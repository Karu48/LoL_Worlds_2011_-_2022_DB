#include "ExtendibleHashing.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include "../struct/register.hpp"

using namespace std;

template<class T>
void ExtendibleHashing<T>::saveBucket(typename ExtendibleHashing<T>::Bucket *bucket, int index) {
    //if the file does not exist, create it
    fstream file(this->fileName, ios::in | ios::out | ios::binary);
    if (!file) {
        file.open(this->fileName, ios::out | ios::binary);
        file.close();
        file.open(this->fileName, ios::in | ios::out | ios::binary);
    }

    file.seekp(index * sizeof(Bucket));
    file.write((char *) bucket, sizeof(Bucket));
    file.close();
}


template<typename T>
typename ExtendibleHashing<T>::Bucket *ExtendibleHashing<T>::loadBucket(int index) {
    fstream file(this->fileName, ios::in | ios::binary);
    auto *bucket = new Bucket();
    file.seekg(index * sizeof(Bucket));
    file.read((char *) bucket, sizeof(Bucket));
    file.close();
    return bucket;
}

template<class T>
void ExtendibleHashing<T>::insert(T record) {
    bitset<sizeof(int) * 8> hashValue = hash(record);
    bitset<sizeof(int) * 8> currentSearch = hashValue & bitset<32>(1);

    int currentDepth = 0;

    while( (directory.find(currentSearch.to_string().substr((sizeof(int) * 8) - (currentDepth + 1), currentDepth + 1 )) == directory.end()) && (currentDepth < globalDepth - 1) ) {
        currentDepth++;
        currentSearch = (hashValue & bitset<32>((1 << (currentDepth + 1)) - 1));
    }

    int index = directory[currentSearch.to_string().substr((sizeof(int) * 8) - (currentDepth + 1), currentDepth + 1)];

    auto bucket = loadBucket(index);

    if (bucket->next != -1) {
        while (bucket->next != -1) {
            index = bucket->next;
            bucket = loadBucket(bucket->next);
        }
    }

    bucket->insert(record);
    saveBucket(bucket, index);
    if (bucket->isFull()) {
        splitBucket(currentDepth, currentSearch.to_string().substr((sizeof(int) * 8) - (currentDepth + 1), currentDepth + 1));
    }
}

template<typename T>
void ExtendibleHashing<T>::splitBucket(int depth, string key) {
    int bucketIndex = directory[key];
    auto *bucket = loadBucket(bucketIndex);

    while (bucket->next != -1) {
        bucketIndex = bucket->next;
        bucket = loadBucket(bucket->next);
    }

    if (bucket->localDepth >= globalDepth - 1) {
        addOverflowBucket(bucketIndex);
        return;
    }

    auto *newBucket = new Bucket();

    T* temp = new T[maxBucketSize];
    for (int i = 0; i < bucket->size; i++) {
        temp[i] = bucket->records[i];
    }

    int totalRecords = bucket->size;
    bucket->size = 0;

    for (int i = 0; i < totalRecords; i++) {
        if (hash(temp[i]).test(depth+1) == 0) {
            bucket->insert(temp[i]);
        } else {
            newBucket->insert(temp[i]);
        }
    }

    directory.erase(key);

    string newKey1 = "0" + key;
    string newKey2 = "1" + key;

    bucket->localDepth++;
    newBucket->localDepth = bucket->localDepth;

    saveBucket(bucket, bucketIndex);
    saveBucket(newBucket, buckets);

    directory[newKey1] = bucketIndex;
    directory[newKey2] = buckets++;

    if (bucket->isFull()) {
        splitBucket((depth + 1), newKey1);
    }
    if (newBucket->isFull()) {
        splitBucket((depth + 1), newKey2);
    }
}

template<typename T>
void ExtendibleHashing<T>::addOverflowBucket(int index) {
    auto bucket = loadBucket(index);
    if (bucket->size < 1) {
        return;
    }
    auto newBucket = new Bucket(bucket->localDepth);

    newBucket->insert(bucket->removeLast());

    bucket->next = buckets;

    saveBucket(bucket, index);
    saveBucket(newBucket, buckets++);
}

template<class T>
void ExtendibleHashing<T>::deleteItem(T record) {
    bitset<sizeof(int) * 8> hashValue = hash(record);
    bitset<sizeof(int) * 8> currentSearch = hashValue & bitset<32>(1);

    int currentDepth = 0;

    while( (directory.find(currentSearch.to_string().substr((sizeof(int) * 8) - (currentDepth + 1), currentDepth + 1 )) == directory.end()) && (currentDepth < globalDepth - 1) ) {
        currentDepth++;
        currentSearch = (hashValue & bitset<32>((1 << (currentDepth + 1)) - 1));
    }

    int index = directory[currentSearch.to_string().substr((sizeof(int) * 8) - (currentDepth + 1), currentDepth + 1)];

    auto bucket = loadBucket(index);

    bool deleted = false;
    if (bucket->contains(record)) {
        bucket->remove(record);
        saveBucket(bucket, index);
        deleted = true;
    }
    int previousIndex = index;
    if (!deleted) {
        if (bucket->next != -1) {
            while (bucket->next != -1 && !bucket->contains(record)) {
                previousIndex = index;
                index = bucket->next;
                bucket = loadBucket(index);
            }
        }
        if (!bucket->contains(record)) {
            return;
        }
        bucket->remove(record);
        saveBucket(bucket, index);
    }
    if (bucket->isEmpty()) {
        cout << "Bucket is empty\n";
        if (previousIndex != index) {
            cout << "Bucket is overflow bucket";
            bucket = loadBucket(index);
            auto previousBucket = loadBucket(previousIndex);
            previousBucket->next = bucket->next;
            saveBucket(previousBucket, previousIndex);
        } else {
            bool done = false;
            // Check if sibling bucket (same key up to its most significant bit (ie 101 and 001 are siblings)) has records
            while (!done && currentDepth > 0) {
                string key = currentSearch.to_string().substr((sizeof(int) * 8) - (currentDepth + 1), currentDepth + 1);
                string siblingKey = key;
                siblingKey[0] = (siblingKey[0] == '0') ? '1' : '0';
                int siblingIndex = directory[siblingKey];
                auto siblingBucket = loadBucket(siblingIndex);

                // if both buckets are empty, we can delete them and make a parent key (one with less depth (ie. 01 is a parent for 001 and 101)) an entry in the directory
                // we can reuse the lowest index of one of the siblings (to avoid creating a new bucket in memory)
                int lowestIndex = (index < siblingIndex) ? index : siblingIndex;
                if (siblingBucket->isEmpty()) {
                    cout << "Sibling bucket is empty\n";
                    directory.erase(key);
                    directory.erase(siblingKey);
                    directory[key.substr(1, key.size() - 1)] = lowestIndex;
                    currentDepth--;
                } else {
                    done = true;
                }
            }
        }
    }
    else if (bucket->next != -1) {
        cout << "Bucket has next\n";
        // we can bring an item from its next bucket to the current bucket
        auto nextBucket = loadBucket(bucket->next);
        bucket->insert(nextBucket->removeLast());
        if (nextBucket->isEmpty()) {
            bucket->next = nextBucket->next;
            saveBucket(bucket, index);
        } else {
            saveBucket(bucket, index);
            saveBucket(nextBucket, bucket->next);
        }
    }
    if (currentDepth != 0 && previousIndex == index && bucket->next == -1) {
        cout << "Possible merge\n";
        // We might want to merge the bucket with a sibling Jinto its parent.
        bool done = false;
        while (!done && currentDepth > 0) {
            string key = currentSearch.to_string().substr((sizeof(int) * 8) - (currentDepth + 1), currentDepth + 1);
            string siblingKey = key;
            siblingKey[0] = (siblingKey[0] == '0') ? '1' : '0';
            if (directory.find(siblingKey) == directory.end()) {
                done = true;
                continue;
            }
            int siblingIndex = directory[siblingKey];
            auto siblingBucket = loadBucket(siblingIndex);

            if (siblingBucket->size + bucket->size < maxBucketSize && siblingBucket->next == -1) {
                cout << "Merging\n";
                // Parent bucket is not a bucket as it's been split before
                // We can reuse the lowest index of the sibling and merge the two buckets
                int lowestIndex = (index < siblingIndex) ? index : siblingIndex;
                int biggestIndex = (index > siblingIndex) ? index : siblingIndex;
                auto parentBucket = new Bucket();
                parentBucket->localDepth = currentDepth - 1;
                parentBucket->size = 0;
                cout << "key: " << key << " siblingKey: " << siblingKey << " lowestIndex: " << lowestIndex << "\n";
                cout << "sibling bucket size: " << siblingBucket->size << " bucket size: " << bucket->size << "\n";
                int initialSiblingSize = siblingBucket->size;
                int initialBucketSize = bucket->size;
                for (int i = 0; i < initialSiblingSize; i++) {
                    parentBucket->insert(siblingBucket->removeLast());
                }
                for (int i = 0; i < initialBucketSize; i++) {
                    parentBucket->insert(bucket->removeLast());
                }
                saveBucket(bucket, biggestIndex);
                saveBucket(parentBucket, lowestIndex);
                directory.erase(key);
                directory.erase(siblingKey);
                directory[key.substr(1, key.size() - 1)] = lowestIndex;
                cout << "Parent key: " << key.substr(1, key.size() - 1) << " index: " << lowestIndex << "\n";
                currentDepth--;
                bucket = parentBucket;
                this->printAllBucketsFromDir();
                this->printAllBucketsFromMemory();
            } else {
                done = true;
            }
        }
    }
}

template<class T>
bool ExtendibleHashing<T>::search(T record) {
    bitset<sizeof(int) * 8> hashValue = hash(record);
    bitset<sizeof(int) * 8> currentSearch = hashValue & bitset<32>(1);

    int currentDepth = 0;

    while( (directory.find(currentSearch.to_string().substr((sizeof(int) * 8) - (currentDepth + 1), currentDepth + 1 )) == directory.end()) && (currentDepth < globalDepth - 1) ) {
        currentDepth++;
        currentSearch = (hashValue & bitset<32>((1 << (currentDepth + 1)) - 1));
    }

    int index = directory[currentSearch.to_string().substr((sizeof(int) * 8) - (currentDepth + 1), currentDepth + 1)];

    auto bucket = loadBucket(index);

    if (bucket->contains(record)) {
        return true;
    }

    if (bucket->next != -1) {
        while (bucket->next != -1 && !bucket->contains(record)) {
            bucket = loadBucket(bucket->next);
        }
    }

    return bucket->contains(record);
}

template<class T>
T ExtendibleHashing<T>::searchByKey(variant<int, float, string> key, string keyType, string type) {
    T tempRecord = T();
    tempRecord.setKey(key, type, keyType);
    bitset<sizeof(int) * 8> hashValue = hash(tempRecord);
    bitset<sizeof(int) * 8> currentSearch = hashValue & bitset<32>(1);

    int currentDepth = 0;

    while( (directory.find(currentSearch.to_string().substr((sizeof(int) * 8) - (currentDepth + 1), currentDepth + 1 )) == directory.end()) && (currentDepth < globalDepth - 1) ) {
        currentDepth++;
        currentSearch = (hashValue & bitset<32>((1 << (currentDepth + 1)) - 1));
    }

    int index = directory[currentSearch.to_string().substr((sizeof(int) * 8) - (currentDepth + 1), currentDepth + 1)];

    auto bucket = loadBucket(index);

    if (bucket->containsByKey(key)) {
        return bucket->searchByKey(key);
    }

    if (bucket->next != -1) {
        while (bucket->next != -1 && !bucket->containsByKey(key)) {
            bucket = loadBucket(bucket->next);
        }
    }

    if (!bucket->containsByKey(key)) {
        return T();
    }

    return bucket->searchByKey(key);
}


bitset<sizeof(int) * 8> CustomHash(Register record) {
        auto key = visit([](auto&& arg) { return arg.getKey(); }, record.data);
        int x = 0;
        memcpy(&x, &key, sizeof(int));
        return bitset<sizeof(int) * 8>(x % 9);
    }

template<typename T>
int ExtendibleHashing<T>::maxBucketSize = 3; // Initialize with a default value

template<typename T>
int ExtendibleHashing<T>::globalDepth = 6;


int main(){
    vector<Register> records;
    ExtendibleHashing<Register> eh("data.dat", 6, 3, CustomHash);
    string data = "12,Play in,MAD_Lions,UNF0RGIVEN,12,6,6,50.0,4.0,2.25,5.08,4.04,284.75,8.99,13.7,433,16400.0,516.0,67.3,29.6,23.7";
    Register r1(data, "damage", "player");
    records.push_back(r1);
    eh.insert(r1);
    data = "12,Play in,Royal_Never_Give_Up,Breathe,9,7,2,77.8,4.22,2.33,4.33,3.67,284.0,8.62,14.1,429,17400.0,528.0,47.5,23.5,21.8";
    Register r2 = Register(data, "damage", "player");
    records.push_back(r2);
    eh.insert(r2);
    data = "12,Play in,Royal_Never_Give_Up,Wei,9,7,2,77.8,3.67,1.44,8.78,8.62,183.89,5.58,12.2,370,11700.0,355.0,69.1,20.4,18.8";
    Register r3 = Register(data, "damage", "player");
    records.push_back(r3);
    eh.insert(r3);
    data = "12,Main,Cloud9,Fudge,6,1,5,16.7,0.83,2.17,2.5,1.54,212.67,7.82,9.0,332,9500.0,348.0,50.0,12.5,20.7";
    Register r4 = Register(data, "damage", "player");
    records.push_back(r4);
    eh.insert(r4);
    data = "12,Main,CTBC_Flying_Oyster,Koala,6,1,5,16.7,0.83,4.83,4.17,1.03,37.33,1.18,7.4,235,5100.0,161.0,62.5,10.4,13.9";
    Register r5 = Register(data, "damage", "player");
    records.push_back(r5);
    eh.insert(r5);
    data = "12,Main,DRX,BeryL,21,14,7,66.7,0.76,2.24,8.0,3.91,34.62,1.0,8.6,250,10200.0,295.0,66.7,5.8,13.7";
    Register r6 = Register(data, "damage", "player");
    records.push_back(r6);
    eh.insert(r6);
    data = "12,Main,DWG_KIA,Canyon,12,7,5,58.3,3.42,2.67,6.75,3.81,176.67,5.59,11.3,358,13300.0,421.0,70.1,23.6,19.5";
    Register r7 = Register(data, "damage", "player");
    records.push_back(r7);
    eh.insert(r7);
    data = "12,Main,EDward_Gaming,Flandre,11,6,5,54.5,2.09,1.82,4.18,3.45,272.45,8.14,12.7,380,16600.0,495.0,47.9,16.0,21.2";
    Register r8 = Register(data, "damage", "player");
    records.push_back(r8);
    eh.insert(r8);
    data = "12,Main,Evil_Geniuses_2e-NA,Vulcan,6,1,5,16.7,0.17,3.67,6.33,1.77,21.83,0.76,6.2,215,4500.0,155.0,73.6,1.9,13.0";
    Register r9 = Register(data, "damage", "player");
    records.push_back(r9);
    eh.insert(r9);
    data = "12,Main,100_Thieves,Abbedagge,6,1,5,16.7,1.83,2.83,3.83,2.0,262.67,8.54,11.6,378,14200.0,463.0,64.2,20.8,22.6";
    Register r10 = Register(data, "damage", "player");
    records.push_back(r10);
    eh.insert(r10);



    eh.printAllBucketsFromDir();
    eh.printAllBucketsFromMemory();

    // cout << "\nChecking if records exist" << endl;
    // for (auto i : records) {
    //     cout << "Record ";
    //     auto x = visit([](auto&& arg) { return arg.getKey(); }, i.data);
    //     if (x.index() == 0){
    //         cout << get<int>(x) << " ";
    //     } else if (x.index() == 1){
    //         cout << get<float>(x) << " ";
    //     } else {
    //         cout << get<string>(x) << " ";
    //     }
    //     cout  << " exists: " << eh.search(i) << endl;
    // }

    cout << "\nDeleting 6, 2 and 7" << endl;
    cout << "\nDeleting 6" << endl;
    eh.deleteItem(r6);
    cout << "\nDeleted 6" << endl;
    eh.printAllBucketsFromDir();
    eh.printAllBucketsFromMemory();
    cout << "\nDeleting 2" << endl;
    eh.deleteItem(r2);
    cout << "\nDeleted 2" << endl;
    eh.printAllBucketsFromDir();
    eh.printAllBucketsFromMemory();
    cout << "\nDeleting 7" << endl;
    eh.deleteItem(r7);
    cout << "\nDeleted 7" << endl;
    eh.printAllBucketsFromDir();
    eh.printAllBucketsFromMemory();

    cout << "\nChecking if records exist" << endl;
    for (auto i : records) {
        cout << "Record ";
        auto x = visit([](auto&& arg) { return arg.getKey(); }, i.data);
        if (x.index() == 0){
            cout << get<int>(x) << " ";
        } else if (x.index() == 1){
            cout << get<float>(x) << " ";
        } else {
            cout << get<string>(x) << " ";
        }
        cout  << " exists: " << eh.search(i) << endl;
    }

    cout << "\nSearching by key 16600" << endl;
    auto result = eh.searchByKey(16600, "damage", "player");
    cout << "Result: ";
    visit([](auto&& arg){ arg.print(); }, result.data);
    cout << endl;
    return 0;
}