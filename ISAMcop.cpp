#define TAM_PAGE 256

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
#include <cmath>
#include <iomanip>

using namespace std;

struct Record {
    int id;         // Identificador único del registro
    char name[20];  // Nombre o descripción del registro
    int ciclo;     // Algún valor asociado al registro
    
    Record(){
        id = 0;
        strcpy(name, "");
        ciclo = 0;
    }
    Record(int id, char* name, int ciclo){
        this->id = id;
        strcpy(this->name, name);
        this->ciclo = ciclo;
    }
};

template<typename TK>
static constexpr size_t m = (TAM_PAGE - sizeof(int) - sizeof(long)) / (sizeof(TK) + sizeof(long));

template <typename TK>
struct IndexPage {
    TK keys[m<TK>];
    long pages[m<TK> + 1];
    int size_keys;
    
    IndexPage(){
        size_keys = 0;
    }
};

static constexpr int M = (TAM_PAGE - sizeof(int) - sizeof(long)) / (sizeof(Record));

struct DataPage{
    Record records[M];
    long nextPage; // Overflow
    int size_records;
    
    DataPage(){
        size_records = 0;
        nextPage = -1;
    }
    
    // has space
    bool hasSpace() {
        // Verifica si la página de datos actual tiene espacio para más registros
        return size_records < M;
    }
    
    // insert record
    void insertRecord(Record record) {
        // Inserta un registro en la página de datos actual
        records[size_records++] = record;
    }
};

template<typename TK>
class ISAM {
private:
    std::string filename;      // Nombre del archivo de datos
    std::string indexFilename; // Nombre del archivo de índices
    std::map<TK, long> indexes; // Mapa de índices en memoria
public:
    ISAM(const std::string& _filename){
        filename = _filename;
        indexFilename = "idx" + filename;
        
        // Open the file in binary mode
        std::fstream file(indexFilename, std::ios::binary | std::ios::in | std::ios::out);
        
        // Read the index pages
        IndexPage<TK> page;
        while (file.read((char*)&page, sizeof(IndexPage<TK>))) {
            for (int i = 0; i < page.size_keys; i++) {
                indexes[page.keys[i]] = page.pages[i];
            }
        }
        
        // Close the file
        file.close();
    }

    ~ISAM() {}
    
    void add(Record record) {
        // Open the file in binary mode
        std::fstream file(filename, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);

        // Find the index
        auto it = indexes.find(record.id);
        if (it != indexes.end()) {
            // Seek to the position
            file.seekg(it->second);

            // Read the data page
            DataPage page;
            file.read((char*)&page, sizeof(DataPage));

            if (page.hasSpace()) {
                // Insert the record into the page
                page.insertRecord(record);

                // Write the page back to the file
                file.seekp(it->second);
                file.write((char*)&page, sizeof(DataPage));
            } else {
                // The page is full, create an overflow page
                DataPage overflowPage;
                overflowPage.insertRecord(record);

                // Write the overflow page to the end of the file
                file.seekp(0, std::ios::end);
                long overflowAddress = file.tellp();
                file.write((char*)&overflowPage, sizeof(DataPage));

                // Update the nextPage pointer of the original page
                page.nextPage = overflowAddress;
                file.seekp(it->second);
                file.write((char*)&page, sizeof(DataPage));
            }
        } else {
            // This is a new key, create a new data page
            DataPage page;
            page.insertRecord(record);

            // Write the data page to the end of the file
            file.seekp(0, std::ios::end);
            long pageAddress = file.tellp();
            file.write((char*)&page, sizeof(DataPage));

            // Update the index
            indexes[record.id] = pageAddress;
        }

        // Close the file
        file.close();
    }
    
    Record searchRecord(TK key) {
        // Find the index
        auto it = indexes.find(key);
        if (it == indexes.end()) {
            throw std::runtime_error("Key not found");
        }

        // Open the file in binary mode
        std::fstream file(filename, std::ios::binary | std::ios::in);

        // Seek to the position
        file.seekg(it->second);

        // Read the data page
        DataPage page;
        file.read((char*)&page, sizeof(DataPage));

        // Find the record
        for (int i = 0; i < page.size_records; i++) {
            if (page.records[i].id == key) {
                // Close the file
                file.close();

                // Return the record
                return page.records[i];
            }
        }

        // If the record was not found in the main page, check the overflow pages
        while (page.nextPage != -1) {
            // Seek to the overflow page
            file.seekg(page.nextPage);

            // Read the overflow page
            DataPage overflowPage;
            file.read((char*)&overflowPage, sizeof(DataPage));

            // Find the record
            for (int i = 0; i < overflowPage.size_records; i++) {
                if (overflowPage.records[i].id == key) {
                    // Close the file
                    file.close();

                    // Return the record
                    return overflowPage.records[i];
                }
            }

            // Move to the next overflow page
            page = overflowPage;
        }

        // If the record was not found, throw an exception
        throw std::runtime_error("Record not found");
    }
    
    std::vector<Record> searchRange(TK lower, TK upper) {
        std::vector<Record> recordsInRange;

        // Iterate over all records
        for (const auto& index : indexes) {
            // If the key is within the specified range, add the record to the result vector
            if (index.first >= lower && index.first <= upper) {
                recordsInRange.push_back(searchRecord(index.first));
            }
        }

        return recordsInRange;
    }
    
    std::vector<Record> getAllRecords() {
        std::vector<Record> records;

        // Open the file in binary mode
        std::fstream file(filename, std::ios::binary | std::ios::in);

        // Start from the beginning of the file
        file.seekg(0, std::ios::beg);

        while (!file.eof()) {
            // Read the data page
            DataPage page;
            file.read((char*)&page, sizeof(DataPage));

            // Add all records from the data page to the vector
            for (int i = 0; i < page.size_records; i++) {
                records.push_back(page.records[i]);
            }

            // If there is an overflow page, read it
            while (page.nextPage != -1) {
                // Seek to the overflow page
                file.seekg(page.nextPage);

                // Read the overflow page
                DataPage overflowPage;
                file.read((char*)&overflowPage, sizeof(DataPage));

                // Add all records from the overflow page to the vector
                for (int i = 0; i < overflowPage.size_records; i++) {
                    records.push_back(overflowPage.records[i]);
                }

                // Move to the next overflow page
                page = overflowPage;
            }
        }

        // Close the file
        file.close();

        return records;
    }
    
        /*
    void deleteRecord(TK key) {
        // Find the index
        auto it = indexes.find(key);
        if (it == indexes.end()) {
            throw std::runtime_error("Key not found");
        }

        // Open the file in binary mode
        std::fstream file(filename, std::ios::binary | std::ios::in | std::ios::out);

        // Seek to the position
        file.seekg(it->second);

        // Read the data page
        DataPage page;
        file.read((char*)&page, sizeof(DataPage));

        // Find the record and delete it
        bool found = false;
        for (int i = 0; i < page.size_records; i++) {
            if (page.records[i].id == key) {
                // Shift all records after this one to the left
                std::copy(page.records + i + 1, page.records + page.size_records, page.records + i);
                page.size_records--;
                found = true;
                break;
            }
        }

        // If the record was not found in the main page, check the overflow pages
        while (!found && page.nextPage != -1) {
            // Seek to the overflow page
            file.seekg(page.nextPage);

            // Read the overflow page
            DataPage overflowPage;
            file.read((char*)&overflowPage, sizeof(DataPage));

            // Find the record and delete it
            for (int i = 0; i < overflowPage.size_records; i++) {
                if (overflowPage.records[i].id == key) {
                    // Shift all records after this one to the left
                    std::copy(overflowPage.records + i + 1, overflowPage.records + overflowPage.size_records, overflowPage.records + i);
                    overflowPage.size_records--;
                    found = true;
                    break;
                }
            }

            // Write the overflow page back to the file
            file.seekp(page.nextPage);
            file.write((char*)&overflowPage, sizeof(DataPage));

            // Move to the next overflow page
            page = overflowPage;
        }

        // If the record was not found, throw an exception
        if (!found) {
            throw std::runtime_error("Record not found");
        }

        // Write the data page back to the file
        file.seekp(it->second);
        file.write((char*)&page, sizeof(DataPage));

        // Close the file
        file.close();
    }
    */
};

int main(){
    ISAM<int> isam("isaaaaam.dat");
    isam.add(Record(1, "Alice", 1));
    isam.add(Record(2, "Bob", 2));
    isam.add(Record(3, "Charlie", 3));
    isam.add(Record(4, "David", 4));
    isam.add(Record(5, "Eve", 5));
    isam.add(Record(6, "Frank", 6));
    isam.add(Record(7, "Grace", 7));
    isam.add(Record(8, "Heidi", 8));
    isam.add(Record(9, "Ivan", 9));
    isam.add(Record(10, "Judy", 10));
    
    cout << log(M)*(10/M) + 1 << endl;
    
    //isam.deleteRecord(5);
    
    auto records = isam.getAllRecords();
    for (const auto& record : records) {
        std::cout << "ID: " << record.id << ", Name: " << record.name << ", Ciclo: " << record.ciclo << std::endl;
    }
    
    cout << endl;
    
    Record record = isam.searchRecord(3);
    std::cout << "ID: " << record.id << ", Name: " << record.name << ", Ciclo: " << record.ciclo << std::endl;
    
    cout << endl;
    
    auto recordsInRange = isam.searchRange(3, 7);
    for (const auto& record : recordsInRange) {
        std::cout << "ID: " << record.id << ", Name: " << record.name << ", Ciclo: " << record.ciclo << std::endl;
    }
    return 0;
}