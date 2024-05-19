#pragma once
#define MAX_LEVEL 3
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <variant>
#include <cstring>
#include <optional> // Para manejar el caso en que no se encuentren registros
#include "Record.hpp"
#include "rapidcsv.hpp"
#include "buffer.hpp"

using namespace std;
using TPrimaryKey = variant<int,float,string>;

struct IndexPage {
    int pk{}; // pointer a la clave primaria keys[m]
    // 4 bytes
    //TPrimaryKey pk{}; // 4 bytes, 4 bytes, n bytes donde n es el # de chars ptr keys[m]
    long long positionPages{}; // Posición de la página en el archivo de datos pages[m+1]// 8 bytes
};

// Contadores de accesos a memoria secundaria
int contadorLecturaIndexfile = 0;
int contadorEscrituraIndexfile = 0;
int contadorLecturaDatafile = 0;
int contadorEscrituraDatafile = 0;

class ISAM {
private:
    string datafilename;
    string indexfilename;

    // static para que las funciones puedan ser llamadas sin instanciar la clase
    // fstream para optimizar la apertura y cierre de archivos
    static bool readIndex(IndexPage &indexRecord, ifstream &file) {
        file.read((char*)&indexRecord, sizeof(indexRecord));
        contadorLecturaIndexfile++;
        return file.good();
    }

    static bool readIndex(IndexPage &indexRecord, fstream &file) {
        file.read((char*)&indexRecord, sizeof(indexRecord));
        contadorLecturaIndexfile++;
        return file.good();
    }

    static bool writeIndex(IndexPage &indexRecord, ofstream &file) {
        file.write(reinterpret_cast<const char*>(&indexRecord), sizeof(indexRecord));
        contadorEscrituraIndexfile++;
        return file.good();
    }

    static bool writeIndex(IndexPage &indexRecord, fstream &file) {
        file.write((char*)&indexRecord, sizeof(IndexPage));
        return file.good();
    }

    
    static bool readRecord(Record &record, ifstream &file) {
        Buffer buffer;
        if (!buffer.read(file)) return false;
        record.unpack(buffer);
        contadorLecturaDatafile++;
        return buffer.read(file);
    }

    static bool writeRecord(Record &record, ofstream &file, unsigned long &defaultpos) {
        Buffer buffer;
        record.pack(buffer);
        contadorEscrituraDatafile++;
        return buffer.write(file);
    }

public:
    explicit ISAM(string filename = "datafile.dat"): datafilename(move(filename))  {
        indexfilename = "indexfile.dat";
    };

    void printIndex(); // getall de los registros del index
    void printAll(); // getall de los registros
    void loadCSV(const string&); // Carga los datos de un archivo CSV
    

    void insert(Record); // Inserta un registro
    optional<Record> search(int); // Busca un registro por su ID, optional para manejar el caso en que no se encuentre
    vector<Record> rangeSearch(int, int); // Busca registros en un rango de IDs
    bool remove(int); // Elimina un registro

    //optional<Record> search(const TPrimaryKey&); // Busca un registro por su ID, optional para manejar el caso en que no se encuentre
    //vector<Record> rangeSearch(const TPrimaryKey&, const TPrimaryKey&); // Busca registros en un rango de IDs
    //bool remove(const TPrimaryKey&); // Elimina un registro
    //void upLevel();

    // Funciones auxiliares

    // obtener los bytes del archivo
    static long long getFileSize(ifstream&);
    static long long getFileSize(fstream&);
    static long long find(int pk, fstream &file);
    //static long long find(const TPrimaryKey &pk, fstream &file);
};


// Mostrar un registro de un index
static void printIndexRecord(IndexPage &indexRecord) {
    cout << indexRecord.pk << " " << indexRecord.positionPages << endl;
}

// Mostrar todos los registros de un index
void ISAM::printIndex() {
    ifstream index(indexfilename, ios::binary);
    IndexPage indexRecord;
    while(readIndex(indexRecord, index)) {
        printIndexRecord(indexRecord);
    }
}

// get all de los registros

void ISAM::printAll() {
    ifstream data(datafilename, ios::binary | ios::in);
    ifstream index(indexfilename, ios::binary | ios::in);
    IndexPage indexRecord;
    Record record;
    while (readIndex(indexRecord, index)) {
        data.seekg(indexRecord.positionPages);
        if (!readRecord(record, data)) break;
        record.print();
    }
}

// Cargar los datos de un archivo CSV con la libreria rapidcsv
void ISAM::loadCSV(const string& csv_dir) {
    Record record;
    ofstream data(datafilename, ios::out | ios::binary);
    ofstream index(indexfilename, ios::out | ios::binary);
    if(!data) return;
    rapidcsv::Document document(csv_dir);
    auto len = document.GetRowCount();
    unsigned long defaultpos = 0;
    IndexPage indexRecord;

    for(int i = 0 ; i < len ; i++){
        vector<string> row = document.GetRow<string>(i);
        record.loadRecord(row);
        indexRecord.positionPages = data.tellp();
        writeRecord(record, data, defaultpos);
        indexRecord.pk = record.get_key();
        index.write((char*)&indexRecord, sizeof(indexRecord));
    }

    data.close();
    index.close();
}

// obtener los bytes del archivo
long long ISAM::getFileSize(ifstream &file) {
    auto pos = file.tellg();
    file.seekg(0, ios::end);
    auto size = file.tellg();
    file.seekg(pos);
    return size;
}

long long ISAM::getFileSize(fstream &file) {
    auto pos = file.tellg();
    file.seekg(0, ios::end);
    auto size = file.tellg();
    file.seekg(pos);
    return size;
}

// Binary search en el indexpage para encontrar un registro
// ya debe tener filas para buscar
long long ISAM::find(int pk, fstream& file){
    long indexSize = sizeof(IndexPage); // 16 bytes
    long long low = 0;
    long long high = (getFileSize(file) / indexSize) - 1; // Por qué da -1?, entraba en un bucle, solucionado
    long long pos = 0;
    IndexPage indexRecord;

    if (high < 0) return -1;

    while(high >= low) {
        long long mid = (high+low) / 2; // piso de [r+l/2]
        pos = mid * indexSize;
        file.seekg(pos); // mid (indexSize)
        readIndex(indexRecord, file);
        if (indexRecord.pk > pk) high = mid - 1;
        else if (indexRecord.pk < pk) low = mid + 1;
        else return pos;
    }
    
    while(indexRecord.pk < pk) {
        pos += indexSize;
        file.seekg(pos);
        readIndex(indexRecord, file);
    }
    while (indexRecord.pk > pk) {
        pos -= indexSize;
        file.seekg(pos);
        readIndex(indexRecord, file);
    }
    return pos;
}

// Insertar un registro
void ISAM::insert(Record record) {
    // ios::app acceso al final del archivo 
    ofstream data(datafilename, ios::ate | ios::app | ios::binary);
    ofstream createFile(indexfilename, ios::app | ios::binary);
    createFile.close(); // Cierra el archivo después de crearlo
    fstream index(indexfilename, ios::in | ios::out | ios::ate | ios::binary);
    if (!data.is_open() || !index.is_open()) {
        if (!data.is_open()) cout << "Data file not open" << endl;
        if (!index.is_open()) cout << "Index file not open" << endl; // Aquí estaba el problema
        return;
    }

    // Buscar la posición de inserción
    IndexPage indexRecord;
    vector<IndexPage> rewrite;
    unsigned long defaultpos = 0;
    int key = record.get_key();

    auto pos = find(key, index);

    // Si el índice está vacío, simplemente insertar el nuevo registro
    
    if (pos == -1) {
        index.clear(); // Limpiar cualquier error del stream
        index.seekp(0); // Mover el puntero de escritura al inicio
        indexRecord.positionPages = data.tellp(); // index
        indexRecord.pk = key;
        writeRecord(record, data, defaultpos);
        writeIndex(indexRecord, index);
        data.close();
        index.close();
        return;
    }

    index.seekg(0);
    while(index.tellg() <= pos) {
        readIndex(indexRecord, index);
        rewrite.push_back(indexRecord);
    }

    index.seekg(pos + sizeof(IndexPage)); // escribir en la siguiente pagina

    // Escribir el registro en el archivo de datos
    indexRecord.pk = key;
    indexRecord.positionPages = data.tellp();
    rewrite.push_back(indexRecord);
    while(readIndex(indexRecord, index)) {
        rewrite.push_back(indexRecord); // guardar los registros restantes
    }

    writeRecord(record, data, defaultpos);
    data.close();
    index.close();

    // Reescribir el archivo de índices
    ofstream reIndex(indexfilename, ios::out | ios::trunc | ios::binary);
    for(auto & page : rewrite) {
        writeIndex(page, reIndex);
    }
    reIndex.close();
}

// Buscar un registro por su primary key
optional<Record> ISAM::search(int key){
    ifstream data(datafilename, ios::binary);
    ifstream index(indexfilename, ios::binary);
    IndexPage indexRecord;
    Record record;
    long long l = 0;
    long long r = (getFileSize(index) / sizeof(IndexPage)) -1 ;

    // Binary search
    while(r > l) {
        long long mid = (r+l) / 2;
        index.seekg(mid*sizeof(IndexPage));
        readIndex(indexRecord, index);
        if(indexRecord.pk < key) l = mid+1;
        else if (indexRecord.pk > key) r = mid-1;
        else {
            data.seekg(indexRecord.positionPages);
            if (readRecord(record, data)) {
                data.close();
                index.close();
                return record;
            }
            else return nullopt; // si no se pudo leer el registro
        }
    }
    readIndex(indexRecord, index);
    if(indexRecord.pk == key) {
        data.seekg(indexRecord.positionPages);
        if(readRecord(record, data)) {
            printIndexRecord(indexRecord);
            data.close();
            index.close();
            return record;
        }
    } else return nullopt; // si no se encontro el registro
    return nullopt; // si no se encontro el registro
}

// Buscar registros en un rango de segun su primary key

// debe encontrar en el rango de begin y end incluyendo el end
vector<Record> ISAM::rangeSearch(int begin, int end){
    ifstream data(datafilename, ios::binary);
    ifstream index(indexfilename, ios::binary);
    IndexPage indexRecord;
    Record record;
    vector<Record> records;
    long long l = 0;
    long long r = (getFileSize(index) / sizeof(IndexPage)) -1 ;

    // Binary search al begin
    while(r > l) {
        long long mid = (r+l) / 2;
        index.seekg(mid*sizeof(IndexPage));
        readIndex(indexRecord, index);
        if(indexRecord.pk < begin) l = mid+1;
        else if (indexRecord.pk > begin) r = mid-1;
        else {
            data.seekg(indexRecord.positionPages);
            if (readRecord(record, data)) {
                records.push_back(record);
                break;
            }
        }
    }

    // si el primary key aun es menor que el end
    while(indexRecord.pk < end) {
        if(readIndex(indexRecord, index)) {
            data.seekg(indexRecord.positionPages);
            if(readRecord(record, data)) {
                records.push_back(record);
            }
        }
    }
    data.close();
    index.close();
    return records; 
}

// Eliminar un registro por su primary key
bool ISAM::remove(int key) {
    ifstream dataIn(datafilename, ios::binary);
    fstream index(indexfilename, ios::in | ios::out | ios::binary);
    if(!dataIn || !index) return false;
    IndexPage indexRecord;
    Record dataRecord;
    vector<IndexPage> indexRewrite;
    vector<Record> dataRewrite;
    unsigned long defaultpos = 0;

    if(!search(key).has_value()) return false;
    auto pos = find(key, index);
    index.seekg(0);
    // save data before removed record
    while(index.tellg() < pos) {
        readIndex(indexRecord, index);
        indexRewrite.push_back(indexRecord);
        dataIn.seekg(indexRecord.positionPages);
        readRecord(dataRecord, dataIn);
        dataRewrite.push_back(dataRecord);
    }

    readIndex(indexRecord, index);

    // save data after removed record
    while(readIndex(indexRecord, index)) {
        dataIn.seekg(indexRecord.positionPages);
        readRecord(dataRecord, dataIn);
        dataRewrite.push_back(dataRecord);
        indexRewrite.push_back(indexRecord);
    }
    dataIn.close();
    index.close();

    // trunc para reescribir
    ofstream dataOut(datafilename, ios::trunc | ios::binary);
    ofstream indexOut(indexfilename, ios::trunc | ios::binary);
    for(auto & rec : dataRewrite) {
        indexRecord.pk = rec.get_key();
        indexRecord.positionPages = dataOut.tellp();
        writeRecord(rec, dataOut, defaultpos);
        indexOut.write((char*)&indexRecord, sizeof(indexRecord));
    }
    dataOut.close();
    indexOut.close();
    return true;
}