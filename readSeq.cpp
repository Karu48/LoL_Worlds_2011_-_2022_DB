#include "struct/register.hpp"
#include <fstream>

int main() {
    ifstream file("file.dat", ios::binary);
    Register reg;
    int s;
    file.read((char*)&s, sizeof(int));
    cout << s << endl;
    for (int i = 0; i < s; i++) {
        file.read((char*)&reg, sizeof(Register));
        PlayerStats player = get<PlayerStats>(reg.data);
        player.print();
        cout << endl;
    }
    file.close();
    ifstream auxFile("aux_file.dat", ios::binary);
    Register auxReg;
    int auxS;
    auxFile.read((char*)&auxS, sizeof(int));
    cout << auxS << endl;
    for (int i = 0; i < auxS; i++) {
        auxFile.read((char*)&auxReg, sizeof(Register));
        PlayerStats auxPlayer = get<PlayerStats>(auxReg.data);
        auxPlayer.print();
        cout << endl;
    }
    return 0;
}