#include "struct/register.hpp"
#include <fstream>
#include "SequentialFile/SequentialFile.hpp"

void test10(){
    fstream file("data/championStats.csv", ios::in);
    string line;
    getline(file, line);
    SequentialFile sf("seq10.dat");
    for (int i = 0; i < 10; i++){
        getline(file, line);
        Register r(line, "champion", "champion");
        sf.insert(r);
    }
    // vector<Register> x = sf.getRegisters();
    // for (auto a : x){
    //     a.print();
    // }
}

void test100(){
    fstream file("data/championStats.csv", ios::in);
    string line;
    getline(file, line);
    SequentialFile sf("seq100.dat");
    for (int i = 0; i < 100; i++){
        getline(file, line);
        Register r(line, "champion", "champion");
        sf.insert(r);
    }
    // vector<Register> x = sf.getRegisters();
    // for (auto a : x){
    //     a.print();
    // }
}

void test1000(){
    fstream file("data/championStats.csv", ios::in);
    string line;
    getline(file, line);
    SequentialFile sf("seq1000.dat");
    for (int i = 0; i < 1000; i++){
        getline(file, line);
        Register r(line, "champion", "champion");
        sf.insert(r);
    }
    // vector<Register> x = sf.getRegisters();
    // for (auto a : x){
    //     a.print();
    // }
}

int main(){
    test10();

    test100();

    test1000();
    return 0;
}