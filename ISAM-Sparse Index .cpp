#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
struct Registro {
    T key;
    // Compitas aquí tenemos los datos del registro championStats.cvs
};

template <typename T>
class ISAM_Sparse_Index {
private:
    int factorBloqueDatos;
    int factorBloqueIndice;
    int nivelesIndexacion;
    vector<vector<T>> index;
    string dataFileName;

    int findIndex(T key) {
        int i = 0;
        while (i < index.size() - 1 && key >= index[i + 1].front())
            i++;
        return i;
    }

public:
    ISAM_Sparse_Index(int factorBD, int factorBI, int nivelesIdx, string fileName) :
            factorBloqueDatos(factorBD), factorBloqueIndice(factorBI), nivelesIndexacion(nivelesIdx), dataFileName(fileName) {
        index.push_back(vector<T>());
    }

    vector<Registro<T>> search(T key) {
        vector<Registro<T>> result;
        ifstream dataFile(dataFileName, ios::binary);
        if (!dataFile) {
            cerr << "Error: No se pudo abrir el archivo de datos." << endl;
            return result;
        }
        int idx = findIndex(key);
        if (idx >= index.size() || index[idx].empty()) {
            cerr << "Error: No se encontraron registros para la clave proporcionada." << endl;
            return result;
        }
        for (int i = 0; i < index[idx].size(); i++) {
            dataFile.seekg(index[idx][i] * sizeof(Registro<T>));
            Registro<T> temp;
            dataFile.read((char*) &temp, sizeof(Registro<T>));
            if (temp.key == key)
                result.push_back(temp);
        }
        dataFile.close();
        return result;
    }

    vector<Registro<T>> rangeSearch(T beginKey, T endKey) {
        vector<Registro<T>> result;
        int idx = findIndex(beginKey);
        ifstream dataFile(dataFileName, ios::binary);
        if (!dataFile) {
            cerr << "Error: No se pudo abrir el archivo de datos." << endl;
            return result;
        }
        for (int i = idx; i < index.size(); i++) {
            for (auto &key : index[i]) {
                if (key > endKey)
                    break;
                dataFile.seekg(key * sizeof(Registro<T>));
                Registro<T> temp;
                dataFile.read((char*) &temp, sizeof(Registro<T>));
                if (temp.key >= beginKey && temp.key <= endKey)
                    result.push_back(temp);
            }
        }
        dataFile.close();
        return result;
    }

    bool add(Registro<T> registro) {
        ofstream dataFile(dataFileName, ios::binary | ios::app);
        if (!dataFile) {
            cerr << "Error: No se pudo abrir el archivo de datos." << endl;
            return false;
        }
        dataFile.write((char*) &registro, sizeof(Registro<T>));
        dataFile.close();

        // Leer el archivo y actualizar el índice
        ifstream dataReadFile(dataFileName, ios::binary);
        if (!dataReadFile) {
            cerr << "Error: No se pudo abrir el archivo de datos para leer." << endl;
            return false;
        }

        // Limpiar el índice
        index.clear();
        index.push_back(vector<T>());

        T key;
        long pos = 0;
        while (dataReadFile.read((char*) &registro, sizeof(Registro<T>))) {
            key = registro.key;
            index[0].push_back(pos);
            pos++;
        }
        dataReadFile.close();

        // Ordenar el índice
        sort(index[0].begin(), index[0].end());

        // Construir índice multinivel si es necesario
        int blockSize = factorBloqueDatos * factorBloqueIndice;
        int dataSize = index[0].size();
        int totalBlocks = dataSize / blockSize;
        int indexLevel = 0;

        while (totalBlocks > 0) {
            if (totalBlocks > factorBloqueIndice)
                indexLevel++;
            totalBlocks /= factorBloqueIndice;
        }

        if (indexLevel > nivelesIndexacion)
            indexLevel = nivelesIndexacion;

        for (int i = 1; i <= indexLevel; i++) {
            index.push_back(vector<T>());
            int blockSizeIdx = index[i - 1].size() / factorBloqueIndice;
            if (index[i - 1].size() % factorBloqueIndice != 0)
                blockSizeIdx++;

            for (int j = 0; j < index[i - 1].size(); j += blockSizeIdx) {
                index[i].push_back(index[i - 1][j]);
            }
        }

        return true;
    }

    bool remove(T key) {
        ifstream dataFile(dataFileName, ios::binary);
        if (!dataFile) {
            cerr << "Error: No se pudo abrir el archivo de datos." << endl;
            return false;
        }
        ofstream tempFile("temp.dat", ios::binary);
        if (!tempFile) {
            cerr << "Error: No se pudo crear el archivo temporal." << endl;
            dataFile.close();
            return false;
        }

        Registro<T> temp;
        bool found = false;
        while (dataFile.read((char*) &temp, sizeof(Registro<T>))) {
            if (temp.key != key)
                tempFile.write((char*) &temp, sizeof(Registro<T>));
            else
                found = true;
        }
        dataFile.close();
        tempFile.close();

        if (!found) {
            cerr << "Error: No se encontró un registro con la clave proporcionada." << endl;
            removeFile("temp.dat");
            return false;
        }

        removeFile(dataFileName);
        renameFile("temp.dat", dataFileName);

        // Reindexar
        ifstream dataReadFile(dataFileName, ios::binary);
        if (!dataReadFile) {
            cerr << "Error: No se pudo abrir el archivo de datos para leer." << endl;
            return false;
        }

        // Limpiar el índice
        index.clear();
        index.push_back(vector<T>());

        T readKey;
        long pos = 0;
        while (dataReadFile.read((char*) &temp, sizeof(Registro<T>))) {
            readKey = temp.key;
            index[0].push_back(pos);
            pos++;
        }
        dataReadFile.close();

        // Ordenar el índice
        sort(index[0].begin(), index[0].end());

        // Construir índice multinivel si es necesario
        int blockSize = factorBloqueDatos * factorBloqueIndice;
        int dataSize = index[0].size();
        int totalBlocks = dataSize / blockSize;
        int indexLevel = 0;

        while (totalBlocks > 0) {
            if (totalBlocks > factorBloqueIndice)
                indexLevel++;
            totalBlocks /= factorBloqueIndice;
        }

        if (indexLevel > nivelesIndexacion)
            indexLevel = nivelesIndexacion;

        for (int i = 1; i <= indexLevel; i++) {
            index.push_back(vector<T>());
            int blockSizeIdx = index[i - 1].size() / factorBloqueIndice;
            if (index[i - 1].size() % factorBloqueIndice != 0)
                blockSizeIdx++;

            for (int j = 0; j < index[i - 1].size(); j += blockSizeIdx) {
                index[i].push_back(index[i - 1][j]);
            }
        }

        return true;
    }

private:
    void removeFile(const string& fileName) {
        if (std::remove(fileName.c_str()) != 0) {
            cerr << "Error: No se pudo eliminar el archivo " << fileName << endl;
        }
    }

    void renameFile(const string& oldName, const string& newName) {
        if (std::rename(oldName.c_str(), newName.c_str()) != 0) {
            cerr << "Error: No se pudo renombrar el archivo " << oldName << " a " << newName << endl;
        }
    }
};

int main() {
    ISAM_Sparse_Index<int> isam(4, 3, 2, "data.dat"); // Factor de bloque de página de datos, Factor de bloque de página de índice, Niveles de indexación, Nombre del archivo de datos

    // Agregar registros
    isam.add({10});
    isam.add({20});
    isam.add({30});
    isam.add({40});
    isam.add({50});
    isam.add({60});
    isam.add({70});

    // Buscar registros
    vector<Registro<int>> result = isam.search(30);
    cout << "Registros encontrados: ";
    for (auto &r : result) {
        cout << r.key << " ";
    }
    cout << endl;

    // Buscar por rango
    result = isam.rangeSearch(20, 50);
    cout << "Registros en el rango: ";
    for (auto &r : result) {
        cout << r.key << " ";
    }
    cout << endl;

    // Eliminar registro
    isam.remove(30);

    return 0;
}
