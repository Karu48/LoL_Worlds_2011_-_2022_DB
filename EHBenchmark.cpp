#include "ExtendibleHashing/ExtendibleHashing.h"

void test1000(){
    fstream file("data/playerStats.csv", ios::in);
    string line;
    getline(file, line);
    ExtendibleHashing<Register> eh("t1000.dat", 6, 3, CustomHash);
    for (int i = 0; i < 1000; i++){
        getline(file, line);
        Register r(line, "player", "player");
        eh.insert(r);
    }
    // eh.printAllBucketsFromDir();
}

int main(){
    test1000();
    return 0;
}