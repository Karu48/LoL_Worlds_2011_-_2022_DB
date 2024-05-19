#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <fstream>
#include <unordered_map>
#include "../ExtendibleHashing/ExtendibleHashing.h"
#include "../SequentialFile/SequentialFile.hpp"
#include "../ISAMstructs/ISAM.hpp"

using namespace std;

struct Table{
    string name;
    string type;
    string key;

    Table(string name, string type, string key){
        this->name = name;
        this->type = type;
        this->key = key;
    }
};

struct TableFile{
    string filename;

    TableFile(string filename){
        this->filename = filename;
        ifstream file(filename);
        if (file.is_open()){
            file.seekg(0, ios::end);
            if (file.tellg() <= 0){
                file.close();
                ofstream file(filename);
                int size = 0;
                file.write((char*)&size, sizeof(int));
                file.close();
            }
        } else {
            ofstream file(filename);
            int size = 0;
            file.write((char*)&size, sizeof(int));
            file.close();
        }
    }

    void insert(Table t){
        fstream file(filename, ios::binary | ios::in | ios::out);
        int size;
        file.read((char*)&size, sizeof(int));
        file.seekg(sizeof(int) + size * sizeof(Table), ios::beg);
        file.write((char*)&t, sizeof(Table));
        size++;
        file.seekg(0, ios::beg);
        file.write((char*)&size, sizeof(int));
        file.close();
        return;
    }

    Table get(string name){
        fstream file(filename, ios::binary | ios::in | ios::out);
        int size;
        file.read((char*)&size, sizeof(int));
        Table t("", "", "");
        for (int i = 0; i < size; i++){
            file.read((char*)&t, sizeof(Table));
            if (t.name == name){
                file.close();
                return t;
            }
        }
        file.close();
        return Table("", "", "");
    }

    void remove(string name){
        fstream file(filename, ios::binary | ios::in | ios::out);
        int size;
        file.read((char*)&size, sizeof(int));
        Table t("", "", "");
        for (int i = 0; i < size; i++){
            file.read((char*)&t, sizeof(Table));
            if (t.name == name){
                size--;
                file.seekg(sizeof(int) + size * sizeof(Table), ios::beg);
                Table t2("", "", "");
                file.read((char*)&t2, sizeof(Table));
                file.seekg(sizeof(int) + i * sizeof(Table), ios::beg);
                file.write((char*)&t2, sizeof(Table));
                file.seekg(0, ios::beg);
                file.write((char*)&size, sizeof(int));
                file.close();
                return;
            }
        }
    }
};