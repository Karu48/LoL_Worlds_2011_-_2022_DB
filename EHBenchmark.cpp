#include "struct/register.hpp"
#include "ExtendibleHashing/ExtendibleHashing.h"
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

void testInsercion(string filename, int numRegistros) {
    fstream file("data/playerStats.csv", ios::in);
    string line;
    getline(file, line);

    ExtendibleHashing<Register> eh(filename, 6, 3, CustomHash);

    auto start = high_resolution_clock::now();
    int diskAccesses = 0;

    for (int i = 0; i < numRegistros; i++) {
        getline(file, line);
        Register r(line, "player", "player");

        eh.insert(r);
        diskAccesses += 1;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Metricas de insercion para " << numRegistros << " registros:" << endl;
    cout << "Total de accesos al disco duro: " << diskAccesses << endl;
    cout << "Tiempo total de ejecucion en milisegundos: " << duration.count() << " ms" << endl;
}


int main() {
    string filename10 = "t1000.dat";
    string filename500 = "t500.dat";
    string filename1000 = "t100.dat";

    testInsercion(filename1000, 1000);

    testInsercion(filename500, 500);

    testInsercion(filename10, 100);

    return 0;
}
