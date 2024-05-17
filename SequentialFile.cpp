#include "struct/register.hpp"
#include <fstream>
#include <vector>
#include <cmath>

vector<Register> insertionSort(vector<Register> registers){
    vector<Register> sortedRegisters;
    for(int i = 0; i < registers.size(); i++){
        if(sortedRegisters.size() == 0){
            sortedRegisters.push_back(registers[i]);
        }else{
            for(int j = 0; j < sortedRegisters.size(); j++){
                auto iKey = visit([](auto&& arg){return arg.getKey();}, registers[i].data);
                auto jKey = visit([](auto&& arg){return arg.getKey();}, registers[j].data);

                bool ij;

                if (iKey.index() == 2){
                    string a = get<string>(iKey);
                    string b = get<string>(jKey);
                    ij = strcmp(a.c_str(), b.c_str()) > 0;
                }else{
                    ij = iKey > jKey;
                }

                if(ij){
                    sortedRegisters.insert(sortedRegisters.begin() + j, registers[i]);
                    break;
                }
            }
        }
    }
    return sortedRegisters;
}

class SequentialFile {
    private:
        string filename;
        string auxFile;

        void rebuild(){
            ifstream auxFile(this->auxFile, ios::in | ios::binary);
            ifstream file(this->filename, ios::in | ios::binary);
            int auxSize, fileSize;
            auxFile.read((char*)&auxSize, sizeof(int));
            file.read((char*)&fileSize, sizeof(int));
            if (auxSize <= log2(fileSize)) return;
            vector<Register> Registers;
            for(int i = 0; i < fileSize; i++){
                Register reg;
                file.read((char*)&reg, sizeof(Register));
                Registers.push_back(reg);
            }
            for(int i = 0; i < auxSize; i++){
                Register reg;
                auxFile.read((char*)&reg, sizeof(Register));
                Registers.push_back(reg);
            }
            Registers = insertionSort(Registers);
            file.close();
            auxFile.close();
            ofstream newFile(this->filename, ios::out | ios::binary);
            newFile.seekp(0, ios::beg);
            int size = Registers.size();
            newFile.write((char*)&size, sizeof(int));
            for(int i = 0; i < Registers.size(); i++){
                newFile.write((char*)&Registers[i], sizeof(Register));
            }
            ofstream newAuxFile(this->auxFile, ios::out | ios::binary);
            newAuxFile.seekp(0, ios::beg);
            size = 0;
            newAuxFile.write((char*)&size, sizeof(int));
            newAuxFile.close();
        }

    public:
        SequentialFile(string filename){
            this->filename = filename;
            this->auxFile = "aux_" + filename;
            ifstream file(this->filename, ios::in | ios::binary);
            file.seekg(0, ios::end);
            if (file.tellg() == -1){
                ofstream file(this->filename, ios::out | ios::binary);
                int size = 0;
                file.write((char*)&size, sizeof(int));
                file.close();
            }
            ifstream auxFile(this->auxFile, ios::in | ios::binary);
            auxFile.seekg(0, ios::end);
            if (auxFile.tellg() == -1){
                ofstream auxFile(this->auxFile, ios::out | ios::binary);
                int size = 0;
                auxFile.write((char*)&size, sizeof(int));
                auxFile.close();
            }
        }

        SequentialFile(string filename, vector<Register> registers){
            this->filename = filename;
            this->auxFile = "aux_" + filename;

            ofstream file(this->filename, ios::out | ios::binary);
            registers = insertionSort(registers);
            int size = registers.size();
            file.write((char*)&size, sizeof(int));
            for(int i = 0; i < registers.size(); i++){
                file.write((char*)&registers[i], sizeof(Register));
            }
            file.close();
            ifstream auxFile(this->auxFile, ios::in | ios::binary);
            auxFile.seekg(0, ios::end);
            if (auxFile.tellg() == -1){
                ofstream auxFile(this->auxFile, ios::out | ios::binary);
                size = 0;
                auxFile.write((char*)&size, sizeof(int));
                auxFile.close();
            }
        }

        void insert(Register reg){
            ifstream auxFile(this->auxFile, ios::in | ios::binary);
            int size;
            auxFile.read((char*)&size, sizeof(int));
            auxFile.close();
            ofstream writeFile(this->auxFile, ios::out | ios::binary);
            size++;
            writeFile.seekp(0, ios::beg);
            writeFile.write((char*)&size, sizeof(int));
            writeFile.seekp(0, ios::end);
            writeFile.write((char*)&reg, sizeof(Register));
            writeFile.close();
            rebuild();
        }

        Register search(variant<int, float, string> key){
            ifstream file(this->filename, ios::in | ios::binary);
            int low = 0;
            int high;
            file.read((char*)&high, sizeof(int));
            high--;
            while(low <= high){
                int mid = (low + high) / 2;
                file.seekg(sizeof(int) + mid * sizeof(Register), ios::beg);
                Register reg;
                file.read((char*)&reg, sizeof(Register));
                auto regKey = visit([](auto&& arg){return arg.getKey();}, reg.data);
                if (regKey == key){
                    return reg;
                }else {

                    if (regKey.index() == 2){
                        string a = get<string>(key);
                        string b = get<string>(regKey);
                        if (strcmp(a.c_str(), b.c_str()) > 0){
                            low = mid + 1;
                        }else{
                            high = mid - 1;
                        }
                    } else {
                        if (key < regKey){
                            high = mid - 1;
                        }else{
                            low = mid + 1;
                        }
                    }
                }
            }
            return Register();
        }

        vector<Register> searchRange(variant<int, float, string> key1, variant<int, float, string> key2){
            ifstream file(this->filename, ios::in | ios::binary);
            int low = 0;
            int high, mid;
            file.read((char*)&high, sizeof(int));
            high--;
            vector<Register> registers;
            while(low <= high){
                mid = (low + high) / 2;
                file.seekg(sizeof(int) + mid * sizeof(Register), ios::beg);
                Register reg;
                file.read((char*)&reg, sizeof(Register));
                auto regKey = visit([](auto&& arg){return arg.getKey();}, reg.data);
                if (regKey == key1){
                    break;
                } else {
                    if (regKey.index() == 2){
                        string a = get<string>(key1);
                        string b = get<string>(regKey);
                        if (strcmp(a.c_str(), b.c_str()) > 0){
                            low = mid + 1;
                        }else{
                            high = mid - 1;
                        }
                    } else {
                        if (key1 < regKey){
                            high = mid - 1;
                        }else{
                            low = mid + 1;
                        }
                    }
                }
            }

            mid--;
            
            while(true) {
                file.seekg(sizeof(int) + mid * sizeof(Register), ios::beg);
                Register reg;
                file.read((char*)&reg, sizeof(Register));
                auto regKey = visit([](auto&& arg){return arg.getKey();}, reg.data);
                if (regKey.index() == 2){
                    string a = get<string>(key2);
                    string b = get<string>(regKey);
                    if (strcmp(a.c_str(), b.c_str()) > 0){
                        break;
                    }
                } else {
                    if (key2 < regKey){
                        break;
                    }
                }
                bool x;
                if (regKey.index() == 2){
                    string a = get<string>(key2);
                    string b = get<string>(regKey);
                    x = strcmp(a.c_str(), b.c_str()) >= 0;
                }else{
                    x = key2 >= regKey;
                }
                if (x){
                    registers.push_back(reg);
                }
                mid++;
            }

            ifstream auxFile(this->auxFile, ios::in | ios::binary);
            int auxSize;
            auxFile.read((char*)&auxSize, sizeof(int));
            for (int i = 0; i < auxSize; i++){
                Register reg;
                auxFile.read((char*)&reg, sizeof(Register));
                auto regKey = visit([](auto&& arg){return arg.getKey();}, reg.data);
                bool x, y = false;
                if (regKey.index() == 2){
                    string a = get<string>(key1);
                    string b = get<string>(regKey);
                    x = strcmp(a.c_str(), b.c_str()) <= 0;
                    a = get<string>(key2);
                    y = strcmp(a.c_str(), b.c_str()) >= 0;
                }else{
                    x = key1 <= regKey;
                    y = key2 >= regKey;
                }
                if (x && y){
                    registers.push_back(reg);
                }
            }
            return registers;
        }

        void remove(variant<int, float, string> key){
            ifstream file(this->filename, ios::in | ios::binary);
            int low = 0;
            int high, mid;
            file.read((char*)&high, sizeof(int));
            int size = high;
            high--;
            vector<Register> registers;
            while(low <= high){
                mid = (low + high) / 2;
                file.seekg(sizeof(int) + mid * sizeof(Register), ios::beg);
                Register reg;
                file.read((char*)&reg, sizeof(Register));
                auto regKey = visit([](auto&& arg){return arg.getKey();}, reg.data);
                if (regKey == key){
                    break;
                } else {
                    if (regKey.index() == 2){
                        string a = get<string>(key);
                        string b = get<string>(regKey);
                        if (strcmp(a.c_str(), b.c_str()) > 0){
                            low = mid + 1;
                        }else{
                            high = mid - 1;
                        }
                    } else {
                        if (key < regKey){
                            high = mid - 1;
                        }else{
                            low = mid + 1;
                        }
                    }
                }
            }
            if (low <= high) {
                file.seekg(sizeof(int) + size * sizeof(Register), ios::beg);
                Register r;
                file.read((char*)&r, sizeof(Register));
                file.close();
                ofstream writeFile(this->auxFile, ios::out | ios::binary);
                writeFile.seekp(sizeof(int) + mid * sizeof(Register), ios::beg);
                writeFile.write((char*)&r, sizeof(Register));
                writeFile.close();
                return;
            } else {
                file.close();
                ifstream auxFile(this->auxFile, ios::in | ios::binary);
                int auxSize;
                auxFile.read((char*)&auxSize, sizeof(int));
                for (int i = 0; i < auxSize; i++){
                    Register reg;
                    auxFile.read((char*)&reg, sizeof(Register));
                    auto regKey = visit([](auto&& arg){return arg.getKey();}, reg.data);
                    if (regKey == key){
                        Register r;
                        auxFile.seekg(sizeof(int) + auxSize * sizeof(Register), ios::beg);
                        auxFile.read((char*)&r, sizeof(Register));
                        auxFile.close();
                        ofstream newAuxFile(this->auxFile, ios::out | ios::binary);
                        auxSize--;
                        newAuxFile.write((char*)&auxSize, sizeof(int));
                        newAuxFile.seekp(sizeof(int) + i * sizeof(Register), ios::beg);
                        newAuxFile.write((char*)&r, sizeof(Register));
                        newAuxFile.close();
                        return;
                    }
                }
                return;
            }
        }
};

int main(){
    SequentialFile file("file.dat");
    string data = "11,Main,T1,Faker,14,10,4,71.4,1.86,1.43,4.79,4.65,252.64,8.14,11.8,381,11200.0,360.0,56.7,15.9,20.8";
    Register reg1(data, "player", "player");
    data = "11,Main,T1,Gumayusi,14,10,4,71.4,3.5,1.0,3.71,7.21,316.57,10.2,14.1,455,14600.0,471.0,61.6,29.9,24.9";
    Register reg2(data, "player", "player");
    data = "11,Main,T1,Keria,14,10,4,71.4,0.57,1.21,8.57,7.53,27.07,0.87,7.7,248,3800.0,123.0,78.0,4.9,13.5";
    Register reg3(data, "player", "player");
    file.insert(reg1);
    file.insert(reg2);
    file.insert(reg3);
    Register reg = file.search("Gumayusi");
    PlayerStats player = get<PlayerStats>(reg.data);
    player.print();
    return 0;

}