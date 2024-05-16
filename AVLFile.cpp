#include "struct/matchStats.hpp"
#include "struct/playerStats.hpp"
#include "struct/championStats.hpp"
#include "struct/register.hpp"
#include <fstream>
#include <vector>
#include <algorithm>

struct AVLNode {
    Register registro;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const Register& data){
        registro = data;
        left = nullptr;
        right = nullptr;
        height = 1;
    }

    AVLNode() {
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AVLFile {
private:
    string filename;
public:
    AVLFile(string filename) : filename(filename), pos_root(0), root(nullptr) {
        ifstream file(filename, ios::binary);
        int pos_root = 0;
        if (file.is_open()) {
            file.seekg(0, ios::end);
            if (file.tellg() != 0) {
                file.read((char*)&pos_root, sizeof(pos_root));
                file.close();
            } else {
                file.close();
                ofstream writeFile(filename, ios::binary);
                writeFile.write((char*)&pos_root, sizeof(pos_root));
                writeFile.close();
            }
        }
    }

    ~AVLFile() {}

    Register find(variant<int, float, string> key) {
        AVLNode node = findNode(readRoot(), key);
        if (node) {
            return node->registro;
        } else {
            return {};
        }
    }

    void insert(const Register& registro) {
        insertNode(read, registro);
    }

    void remove(variant<int, float, string> key) {
        root = deleteNode(root, key);
        writeNode(root, pos_root);
    }

    vector<Register> inorder() {
        vector<Register> registers;
        inorderTraversal(root, registers);
        return registers;
    }

    AVLNode* getRoot() {
        return root;
    }

    vector<Register> rangeSearch(variant<int, float, string> low, variant<int, float, string> high) {
        vector<Register> result;
        rangeSearchHelper(root, low, high, result);
        return result;
    }

private:
    AVLNode findNode(long node, variant<int, float, string> key) {
        if (node == -1)
            return nullptr;

        AVLNode nodeData = readNode(node);
        auto keyNode = visit([](auto&& arg){return arg.getKey();}, nodeData->registro.data);

        if (key < keyNode)
            if (node->left == nullptr) return nullptr;
            return findNode(node->left, key);
        else if (key > keyNode)
            if (node->right == nullptr) return nullptr;
            return findNode(node->right, key);
        else
            return node;
    }

    int height(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int balanceFactor(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    void updateHeight(AVLNode* node) {
        if (node == nullptr)
            return;
        node->height = 1 + max(height(node->left), height(node->right));
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* z = x->right;

        x->right = y;
        y->left = z;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* z = y->left;

        y->left = x;
        x->right = z;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    AVLNode* insertNode(AVLNode* node, const Register& registro) {
        if (node == nullptr)
            return new AVLNode(registro);

        auto keyNode = visit([](auto&& arg){return arg.getKey();}, node->registro.data);

        auto keyRegistro = visit([](auto&& arg){return arg.getKey();}, registro.data);

        if (keyRegistro < keyNode)
            node->left = insertNode(node->left, registro);
        else if (keyRegistro > keyNode)
            node->right = insertNode(node->right, registro);
        else
            return node;

        updateHeight(node);

        int balance = balanceFactor(node);

/*
        if (balance > 1 and registro.data.getKey() < node->left->registro.data.getKey())
            return rotateRight(node);

        if (balance < -1 and registro.data.getKey() > node->right->registro.data.getKey())
            return rotateLeft(node);

        if (balance > 1 and registro.data.getKey() > node->left->registro.data.getKey()) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 and registro.data.getKey() < node->right->registro.data.getKey()) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
*/
        if (balance >= 2) {
            if (balanceFactor(node->left) >= 0)
                return rotateRight(node);
            else {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }

        if (balance <= -2) {
            if (balanceFactor(node->right) <= 0)
                return rotateLeft(node);
            else {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }

        return node;
    }

    AVLNode* deleteNode(AVLNode* node, variant<int, float, string> key) {
        if (node == nullptr)
            return node;

        auto keyNode = visit([](auto&& arg){return arg.getKey();}, node->registro.data);

        if (key < keyNode)
            node->left = deleteNode(node->left, key);
        else if (key > keyNode)
            node->right = deleteNode(node->right, key);
        else {
            if (node->left == nullptr || node->right == nullptr) {
                AVLNode* temp = node->left ? node->left : node->right;

                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else
                    *node = *temp;

                delete temp;
            } else {
                AVLNode* temp = minValueNode(node->right);
                node->registro = temp->registro;
                auto keytemp = visit([](auto&& arg){return arg.getKey();}, temp->registro.data);
                node->right = deleteNode(node->right, keytemp);
            }
        }

        if (node == nullptr)
            return node;

        updateHeight(node);

        int balance = balanceFactor(node);

        if (balance > 1 && balanceFactor(node->left) >= 0)
            return rotateRight(node);

        if (balance > 1 && balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && balanceFactor(node->right) <= 0)
            return rotateLeft(node);

        if (balance < -1 && balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    void inorderTraversal(AVLNode* node, vector<Register>& registers) {
        if (node == nullptr)
            return;

        inorderTraversal(node->left, registers);
        registers.push_back(node->registro);
        inorderTraversal(node->right, registers);
    }

    void rangeSearchHelper(AVLNode* node, variant<int, float, string> low, variant<int, float, string> high, vector<Register>& result) {
        if (node == nullptr)
            return;

        auto keyNode = visit([](auto&& arg){return arg.getKey();}, node->registro.data);

        if (keyNode > low)
            rangeSearchHelper(node->left, low, high, result);

        if (keyNode >= low && keyNode <= high)
            result.push_back(node->registro);

        if (keyNode < high)
            rangeSearchHelper(node->right, low, high, result);
    }

    void writeNode(AVLNode* node, long& pos) {
        ofstream file(filename, ios::binary | ios::trunc);
        if (!file.is_open()) {
            cerr << "Error: No se puede abrir el archivo para escribirlo." << endl;
            exit(1);
        }

        if (node == nullptr) return;

        file.seekp(pos);
        file.write((char*)node, sizeof(AVLNode));
        file.close();
    }

    AVLNode readNode(long& pos) {
        ifstream file(filename, ios::binary);
        if (!file.is_open()) {
            cerr << "Error: No se puede abrir el archivo para leerlo." << endl;
            exit(1);
        }

        AVLNode node;
        file.seekg(pos);
        file.read((char*)&node, sizeof(AVLNode));
        file.close();

        return node;
    }

    void writeRoot(long& pos) {
        ofstream file(filename, ios::binary | ios::out);
        if (!file.is_open()) {
            cerr << "Error: No se puede abrir el archivo para escribirlo." << endl;
            exit(1);
        }
        file.seekp(0, ios::beg);
        file.write((char*)&pos, sizeof(pos));
        file.close();
    }

    long readRoot() {
        ifstream file(filename, ios::binary);
        if (!file.is_open()) {
            cerr << "Error: No se puede abrir el archivo para leerlo." << endl;
            exit(1);
        }

        long pos;
        file.seekg(0, ios::beg);
        file.read((char*)&pos, sizeof(pos));
        file.close();

        return pos;
    }
};

int main() {
    AVLFile avlFile("data.bin");

    string key = "playedGames";

    string data = "4,Main,Thresh,63,80.8,19.0,44,15.0,24,20,54.5,0.8,3.34,9.84,3.18,31.27,0.88,8.4,237.0,,,68.1,5.1,14.3";

    Register c1(data, key, "champion");

    data = "4,Main,Kha'Zix,66,84.6,8.0,58,18.0,25,33,43.1,2.98,2.57,4.79,3.03,137.84,3.8,10.8,299.0,,,61.1,23.4,18.8";

    Register c2(data, key, "champion");

    data = "4,Main,Janna,53,67.9,8.0,45,14.0,28,17,62.2,0.33,2.11,11.13,5.43,19.87,0.55,9.2,255.0,,,73.5,2.1,15.3";

    Register c3(data, key, "champion");

    avlFile.insert(c1);
    avlFile.insert(c2);
    avlFile.insert(c3);

    Register result = avlFile.find(45);

    // Lo sagrado para imprimir
    // auto variante = visit([result](){return result.data;});
    // visit([](auto x){x.print();}, variante);

    auto resultKey = visit([](auto&& arg){return arg.getKey();}, result.data);
    auto name = std::visit([](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, ChampionStats>) {
            return arg.champion;  // Replace 'attribute1' with the actual attribute name
        } else if constexpr (std::is_same_v<T, MatchStats>) {
            return arg.event;  // Replace 'attribute2' with the actual attribute name
        } else if constexpr (std::is_same_v<T, PlayerStats>) {
            return arg.event;  // Replace 'attribute3' with the actual attribute name
        }
    }, result.data);

    visit([&result](auto x){cout << "Registro encontrado: " << x << ", ";}, resultKey);
    cout << name << endl;


    vector<Register> orderedregisters = avlFile.inorder();
    cout << "Todos los registros ordenados:" << endl;
    for (const auto& registro : orderedregisters) {
        auto resultKey = visit([](auto&& arg){return arg.getKey();}, registro.data);
        auto name = std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, ChampionStats>) {
                return arg.champion;  // Replace 'attribute1' with the actual attribute name
            } else if constexpr (std::is_same_v<T, MatchStats>) {
                return arg.event;  // Replace 'attribute2' with the actual attribute name
            } else if constexpr (std::is_same_v<T, PlayerStats>) {
                return arg.event;  // Replace 'attribute3' with the actual attribute name
            }
        }, registro.data);

        visit([&result](auto x){cout << "Registro encontrado: " << x << ", ";}, resultKey);
        cout << name << endl;
    }


    avlFile.remove(45);
    cout << "Despues de eliminar el registro con Key 45:" << endl;
    orderedregisters = avlFile.inorder();
    for (const auto& registro : orderedregisters) {
        auto resultKey = visit([](auto&& arg){return arg.getKey();}, registro.data);
        auto name = std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, ChampionStats>) {
                return arg.champion;  // Replace 'attribute1' with the actual attribute name
            } else if constexpr (std::is_same_v<T, MatchStats>) {
                return arg.event;  // Replace 'attribute2' with the actual attribute name
            } else if constexpr (std::is_same_v<T, PlayerStats>) {
                return arg.event;  // Replace 'attribute3' with the actual attribute name
            }
        }, registro.data);

        visit([&result](auto x){cout << "Registro encontrado: " << x << ", ";}, resultKey);
        cout << name << endl;
    }


    cout << "Buscando registros en el rango [30, 50]:" << endl;
    vector<Register> rangeResult = avlFile.rangeSearch(30, 50);
    for (const auto& registro : rangeResult) {
        auto resultKey = visit([](auto&& arg){return arg.getKey();}, registro.data);
        // auto name = std::visit([](auto&& arg) {
        //     using T = std::decay_t<decltype(arg)>;
        //     if constexpr (std::is_same_v<T, ChampionStats>) {
        //         return arg.champion;  // Replace 'attribute1' with the actual attribute name
        //     } else if constexpr (std::is_same_v<T, MatchStats>) {
        //         return arg.event;  // Replace 'attribute2' with the actual attribute name
        //     } else if constexpr (std::is_same_v<T, PlayerStats>) {
        //         return arg.event;  // Replace 'attribute3' with the actual attribute name
        //     }
        // }, registro.data);

        ChampionStats c = get<ChampionStats>(registro.data);

        visit([&result](auto x){cout << "Registro encontrado: " << x << ", ";}, resultKey);
        cout << c.champion << endl;
    }

    return 0;
}
