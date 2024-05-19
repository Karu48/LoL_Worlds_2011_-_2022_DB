#include "struct/register.hpp"
#include <fstream>
#include "SequentialFile/SequentialFile.hpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

void testInsercion(string filename, int numRegistros) {
    fstream file("data/championStats.csv", ios::in);
    string line;
    getline(file, line);

    SequentialFile sf(filename);

    auto start = high_resolution_clock::now(); 
    int diskAccesses = 0;

    for (int i = 0; i < numRegistros; i++) {
        getline(file, line);
        Register r(line, "champion", "champion");
        sf.insert(r);
        diskAccesses += 2;
    }

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Metricas de insercion para " << numRegistros << " registros:" << endl;
    cout << "Total de accesos al disco duro: " << diskAccesses << endl;
    cout << "Tiempo total de ejecucion en milisegundos: " << duration.count() << " ms" << endl;
}

void testBusqueda(string filename, variant<int, float, string> key) {
    SequentialFile sf(filename);

    auto start = high_resolution_clock::now(); 
    int diskAccesses = 0;
    
    sf.search(key);
    diskAccesses += 1; 

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Metricas de busqueda para la clave ";
    
    if (holds_alternative<int>(key)) {
        cout << get<int>(key);
    } else if (holds_alternative<float>(key)) {
        cout << get<float>(key);
    } else if (holds_alternative<string>(key)) {
        cout << get<string>(key);
    } else {
        cout << "Tipo de clave no reconocido";
    }

    cout << ":" << endl;
    cout << "Total de accesos al disco duro: " << diskAccesses << endl;
    cout << "Tiempo total de ejecucion en milisegundos: " << duration.count() << " ms" << endl;
}

int main() {
    string filename = "seq1000.dat";

    testInsercion(filename, 1000);

    testInsercion(filename, 100);

    testInsercion(filename, 100);

    testBusqueda(filename, "clave_busqueda");

    return 0;
}