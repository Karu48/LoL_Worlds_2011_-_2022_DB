#ifndef EXTENDIBLEHASHING_EXTENDIBLEHASHING_H
#define EXTENDIBLEHASHING_EXTENDIBLEHASHING_H
#pragma once

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <bitset>
#include <functional>
#include <unordered_map>
#include "../struct/register.hpp"

using namespace std;

bitset<sizeof(int) * 8> CustomHash(Register record) {
        auto key = visit([](auto&& arg) { return arg.getKey(); }, record.data);
        int x = 0;
        memcpy(&x, &key, sizeof(int));
        return bitset<sizeof(int) * 8>(x % 9);
    }

template<class T>
class ExtendibleHashing {
    string fileName;
    static int globalDepth;
    static int maxBucketSize;
    int buckets = 0;
     // Function pointer to hash function
    // Has to be a pointer to allow for different hash functions (we don't know how T looks like)
    std::function<std::bitset<sizeof(int) * 8>(T)> hash;

    unordered_map<string, int> directory;

    //Constructor
public:
     ExtendibleHashing(string fileName) {
        this->fileName = fileName;
        this->globalDepth = 9;
        this->maxBucketSize = 3;
        this->hash = CustomHash;

        // Initialize first two buckets (0 and 1)
        auto *bucket0 = new Bucket();
        auto *bucket1 = new Bucket();
        saveBucket(bucket0, 0);
        saveBucket(bucket1, 1);
        buckets = 2;

        // Initialize directory
        directory["0"] = 0;
        directory["1"] = 1;
     }

    struct Bucket {
        int localDepth;
        int size;
        T *records;
        int next = -1;

        Bucket() {
            this->localDepth = 0;
            this->size = 0;
            this->records = new T[maxBucketSize];
        }

        Bucket(int localDepth) {
            this->localDepth = localDepth;
            this->size = 0;
            this->records = new T[maxBucketSize];
        }

        ~Bucket() {
            delete[] records;
        }

        void insert(T record) {
            records[size++] = record;
            // We don't have to check size here.
            // We'll do it in the insert function of ExtendibleHashing.
            // If it's full, we'll split the bucket.
        }

        // void remove(variant<int, float, string> key, string keyType, string type){
        //     Register tempRecord = Register("", "", "");
        //     tempRecord.setKey(key, type, keyType);
            
        // }

        void remove(T record) {
            for (int i = 0; i < size; i++) {
                if (records[i] == record) {
                    for (int j = i; j < size - 1; j++) {
                        records[j] = records[j + 1];
                    }
                    size--;
                    return;
                }
            }
            cout << "Remove failed: Record not found" << endl;
        }

        void removePos(int pos) {
            for (int i = pos; i < size - 1; i++) {
                records[i] = records[i + 1];
            }
            size--;
        }

        T removeLast() {
            if (size == 0 || size - 1 < 0) {
                cout << "Error: Bucket is empty" << endl;
                exit(1);
            }
            auto record = records[size - 1];
            size--;
            return record;
        }

        bool contains(T record) {
            for (int i = 0; i < size; i++) {
                if (records[i] == record) {
                    return true;
                }
            }
            return false;
        }

        bool containsByKey(variant<int, float, string> key) {
            for (int i = 0; i < size; i++) {
                auto r = visit([](auto &&arg) { return arg.getKey(); }, records[i].data);
                if (r == key) {
                    return true;
                }
            }
            return false;
        }

        T searchByKey(variant<int, float, string> key) {
            for (int i = 0; i < size; i++) {
                auto r = visit([](auto &&arg) { return arg.getKey(); }, records[i].data);
                if (r == key) {
                    return records[i];
                }
            }
            cout << "Search failed: Record not found" << endl;
            exit(1);
        }

        bool isFull() {
            return size >= maxBucketSize;
        }

        bool isEmpty() {
            return size == 0;
        }
    };

public:

    void saveBucket(Bucket *bucket, int index);
    Bucket *loadBucket(int index);

    void insert(T record);

    void printAllBucketsFromDir() {
        // Explore directory, load buckets and print them
        for (auto const &pair : directory) {
            auto *b = loadBucket(pair.second);
            cout << "Bucket " << pair.first << "(" << pair.second << ")" << ": ";
            for (int j = 0; j < b->size; j++) {
                auto r = visit([](auto &&arg) { return arg.getKey(); }, b->records[j].data);
                if (r.index() == 0){
                    cout << get<int>(r) << " ";
                } else if (r.index() == 1){
                    cout << get<float>(r) << " ";
                } else {
                    cout << get<string>(r) << " ";
                }

            }
            while (b->next != -1) {
                cout << "-> ";
                b = loadBucket(b->next);
                for (int j = 0; j < b->size; j++) {
                    auto r = visit([](auto &&arg) { return arg.getKey(); }, b->records[j].data);
                    if (r.index() == 0){
                        cout << get<int>(r) << " ";
                    } else if (r.index() == 1){
                        cout << get<float>(r) << " ";
                    } else {
                        cout << get<string>(r) << " ";
                    }
                }
            }
            cout << endl;
        }
    }

    void printAllBucketsFromMemory() {
        for (int i = 0; i < buckets; i++) {
            auto *b = loadBucket(i);
            cout << "Bucket " << i << ": ";
            for (int j = 0; j < b->size; j++) {
                auto r = visit([](auto &&arg) { return arg.getKey(); }, b->records[j].data);
                if (r.index() == 0){
                    cout << get<int>(r) << " ";
                } else if (r.index() == 1){
                    cout << get<float>(r) << " ";
                } else {
                    cout << get<string>(r) << " ";
                }
            }
            cout << endl;
        }
    }

    void splitBucket(int depth, string key);
    void addOverflowBucket(int index);
    void deleteItem(T record);
    bool search(T record);
    T searchByKey(variant<int, float, string> key, string keyType, string type);
};

template<typename T>
int ExtendibleHashing<T>::maxBucketSize = 3; // Initialize with a default value

template<typename T>
int ExtendibleHashing<T>::globalDepth = 6;

#endif //EXTENDIBLEHASHING_EXTENDIBLEHASHING_H

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