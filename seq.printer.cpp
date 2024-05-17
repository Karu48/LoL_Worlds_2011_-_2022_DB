#include "struct/register.hpp"
#include <fstream>

int main() {
    cout << "Main file:\n";
    ifstream file("file.dat", ios::in | ios::binary);
    int size = 0;
    file.read((char*)&size, sizeof(size));
    cout << size << endl;
    Register r;
    for (int i = 0; i < size; i++) {
        file.read((char*)&r, sizeof(Register));
        visit([](auto&& arg) {
            arg.print();
        }, r.data);
    }
    file.close();
    cout << endl << "Aux file:\n";
    file.open("aux_file.dat", ios::in | ios::binary);
    size = 0;
    file.read((char*)&size, sizeof(size));
    cout << size << endl;
    for (int i = 0; i < size; i++) {
        file.read((char*)&r, sizeof(Register));
        visit([](auto&& arg) {
            arg.print();
        }, r.data);
    }
    file.close();
    return 0;
}