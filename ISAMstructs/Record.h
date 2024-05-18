#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include "buffer.h"
using namespace std;

class Record {
public:
    long initializer;
    vector<string> pre_record; // Guarda los datos de un record
    void print();
    void pack(Buffer &buffer);
    void unpack(Buffer &buffer);
    void loadRecord(vector<string>);
    int get_key() const {return stoi(pre_record[0]);} // primary key del record, columna 0
    Record(): initializer(0) {}
};

// Empaquetar los datos de un record en un buffer
void Record::pack(Buffer &buffer) {
    buffer.clear();
    for (const auto &field : pre_record) {
        buffer.pack(field.data());
    }
}

// Desempaquetar los datos de un buffer en un record
void Record::unpack(Buffer &buffer) {
    char* temp = new char[buffer.get_max_bytes()];
    if (pre_record.empty()) {
        while (buffer.unpack(temp)) {
            string field_str(temp);
            pre_record.push_back(field_str);
        }
    } else {
        for (auto &field : pre_record) {
            if (buffer.unpack(temp)) {
                string field_str(temp);
                field = field_str;
            }
            else throw runtime_error("No se pudo desempaquetar el buffer");
        }
    }
    delete[] temp;
}

// Imprimir los datos de un record campo por campo
void Record::print() {
    for (auto &field : pre_record) cout << field << " ";
    cout << endl;
}

// Cargar los datos de un record
void Record::loadRecord(vector<string> new_data) {
    pre_record = std::move(new_data);
}