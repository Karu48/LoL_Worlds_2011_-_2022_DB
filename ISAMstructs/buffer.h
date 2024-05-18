#pragma once

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Buffer {
    char delimeter;
    char* buffer;
    int buffer_size;
    int max_bytes;
    int next_byte;
public:
    Buffer(char delim = '|', int max_b = 1024){
        delimeter = delim;
        if (max_b < 0) max_b = 0;
        max_bytes = max_b;
        buffer = new char[max_bytes];
        buffer_size = 0;
        next_byte = 0;
    }

    ~Buffer() {delete[] buffer;}

    void clear() {
        next_byte = 0;
        buffer_size = 0;
    }

    bool read(ifstream&);
    bool write(ofstream&) const;
    bool pack(const char*, int size = -1);
    bool unpack(char*);
    int get_buffer_size() const {return buffer_size;}
    unsigned long get_buffer_length() const {return strlen(buffer);}
    int get_max_bytes() const {return max_bytes;}
};

bool Buffer::read(ifstream &stream) {
    clear(); // Reasignamos a 0 el tamaño del buffer
    stream.read((char *)(&buffer_size), sizeof(buffer_size)); // recuperamos el tamaño del buffer
    if (stream.fail()) return false; // si no se pudo leer el tamaño
    if (buffer_size > max_bytes) return false; // si el tamaño excede 1024
    stream.read(buffer, buffer_size);
    return stream.good();
}

bool Buffer::write(ofstream &stream) const {
    stream.write(reinterpret_cast<const char*>(&buffer_size), sizeof(buffer_size));
    stream.write(buffer, buffer_size);
    return stream.good();
}

bool Buffer::pack(const char *str, int size) {
    short updateLenght = 0;
    if (size >= 0) updateLenght = size;
    else updateLenght = strlen(str);
    if (updateLenght > strlen(str)) return false;

    int begin = next_byte;
    next_byte += updateLenght + 1;
    if (next_byte > max_bytes) return false;
    memcpy(&buffer[begin], str, updateLenght); // copy string
    buffer[begin + updateLenght] = delimeter; // add delimeter
    buffer_size = next_byte; // update buffer size
    return true;
}

bool Buffer::unpack(char *str) {
    int updateLenght = -1;
    int begin = next_byte;
    for (int i = begin; i < buffer_size; i++) {
        if (buffer[i] == delimeter) {
            updateLenght = i - begin;
            break;
        }
    }
    if (updateLenght == -1) return false;
    next_byte += updateLenght + 1;
    if (next_byte > max_bytes) return false;
    strncpy(str, &buffer[begin], updateLenght);
    str[updateLenght] = 0;
    return true;
}