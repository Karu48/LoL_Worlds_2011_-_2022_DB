// #include "ExtendibleHashing/ExtendibleHashing.h"
// #include <chrono>
// #include <iostream>
// #include <vector>
// #include <string>
// #include <bitset>
// #include <functional>

// using namespace std;

// bitset<sizeof(int) * 8> CustomHash(int record) {
//     return bitset<sizeof(int) * 8>(record % 3);
// }

// void test_insert() {
//     ExtendibleHashing<int> eh2("data/extendibleHashing.bin", 3, 3, CustomHash);

//     // Carga los datos del CSV en el hash extendible
//     eh2.loadCSV("data/championStats.csv");

//     int input;
//     do {
//         cout << "Ingresa un número para insertar: ";
//         cin >> input;
//         if (input <= 0) cout << "Número no válido" << endl;
//     } while (input <= 0);

//     // Mide el tiempo de inicio de la inserción
//     auto inicio_contador = chrono::high_resolution_clock::now();

//     // Inserta el registro en el hash extendible
//     eh2.insert(input);
//     cout << "Registro insertado" << endl;

//     // Mide el tiempo de finalización de la inserción
//     auto fin_contador = chrono::high_resolution_clock::now();
//     cout << "Tiempo de ejecución: " << chrono::duration_cast<chrono::microseconds>(fin_contador - inicio_contador).count() << "us" << endl;
// }

// int main() {
//     test_insert();
//     return 0;
// }
