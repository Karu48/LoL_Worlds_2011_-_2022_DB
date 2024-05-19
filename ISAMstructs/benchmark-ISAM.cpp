#include "ISAM.hpp"
#include <chrono>
#include <variant>
#include <vector>

using namespace std;

void test_insert() {
    ISAM isam;
    isam.loadCSV("data/championStats.csv");
    int input;
    do{
        cout << "Ingresa la season en la que jugo [1 - 12]: ";
        cin >> input;
        if ((input <= 0) || (input >= 13)) cout << "Season no valida";
    } while (input <= 0);

    auto inicio_contador = chrono::high_resolution_clock::now();
    vector<string> rec_to_insert;
    rec_to_insert.emplace_back(to_string(input));
    rec_to_insert.emplace_back("Main");
    rec_to_insert.emplace_back("Fizz");
    rec_to_insert.emplace_back("4");
    rec_to_insert.emplace_back("5.0");
    rec_to_insert.emplace_back("");
    rec_to_insert.emplace_back("4");
    rec_to_insert.emplace_back("2.0");
    rec_to_insert.emplace_back("3");
    rec_to_insert.emplace_back("1");
    rec_to_insert.emplace_back("75.0");
    rec_to_insert.emplace_back("2.5");
    rec_to_insert.emplace_back("1.25");
    rec_to_insert.emplace_back("4.0");
    rec_to_insert.emplace_back("5.2");
    rec_to_insert.emplace_back("275.25");
    rec_to_insert.emplace_back("7.86");
    rec_to_insert.emplace_back("13.2");
    rec_to_insert.emplace_back("375.0");
    rec_to_insert.emplace_back("");
    rec_to_insert.emplace_back("");
    rec_to_insert.emplace_back("76.5");
    rec_to_insert.emplace_back("29.4");
    rec_to_insert.emplace_back("20.6");

    Record record;
    record.loadRecord(rec_to_insert);
    isam.insert(record);
    cout << "Registro insertado" << endl;
    auto fin_contador = chrono::high_resolution_clock::now();
    cout << "Tiempo de ejecucion: " << chrono::duration_cast<chrono::milliseconds>(fin_contador - inicio_contador).count() << " ms" << endl;
    cout << "Lecturas en disco duro: " << contadorLecturaIndexfile + contadorLecturaDatafile << endl;
    cout << "Escrituras en disco duro: " << contadorEscrituraIndexfile + contadorEscrituraDatafile << endl;
}

void test_search(){
    ISAM isam;
    isam.loadCSV("data/championStats.csv");
    int input;
    do{
        cout << "Ingresa la season en la que jugo [1 - 12]: ";
        cin >> input;
        if ((input <= 0)) cout << "Season no valida";
    } while (input <= 0);

    auto inicio_contador = chrono::high_resolution_clock::now();
    auto dataRecord = isam.search(input);
    if(dataRecord.has_value()) dataRecord->print();
    else cout << "No se encontro ningun registro con informacion de que jugo en la season " << input << endl;
    auto fin_contador = chrono::high_resolution_clock::now();
    cout << "Tiempo de ejecucion: " << chrono::duration_cast<chrono::milliseconds>(fin_contador - inicio_contador).count() << " ms" << endl;
}

// Si el key se repite, solo muestra los ultimos registros del begin y uno solo del end
void test_search_in_range(){
    ISAM isam;
    isam.loadCSV("data/championStats.csv");
    int input1, input2;
    do{
        cout << "Ingresa el rango de temporadas a buscar [ingresa la primera, enter, y ingresa la segunda]: ";
        cin >> input1 >> input2;
        if ((input1 <= 0 || input2 <= 0) || (input1 >= 13 || input2 >= 13)) cout << "Season no valida";
    } while (input1 <= 0 || input2 <= 0);

    auto inicio_contador = chrono::high_resolution_clock::now();
    auto records = isam.rangeSearch(input1, input2);
    if(!records.empty()){
        for(auto r : records){
            r.print();
        }
    } else {
        cout << "No records found" << endl;
    }
    auto fin_contador = chrono::high_resolution_clock::now();
    cout << "Tiempo de ejecucion: " << chrono::duration_cast<chrono::milliseconds>(fin_contador - inicio_contador).count() << "ms" << endl;
}

void test_remove(){
    ISAM isam;
    isam.loadCSV("data/championStats.csv");
    int input;
    do{
        cout << "Ingresa la season en la que jugo [1 - 12]: ";
        cin >> input;
        if ((input <= 0) || (input >= 13)) cout << "Season no valida";
    } while (input <= 0);

    auto inicio_contador = chrono::high_resolution_clock::now();
    bool removed = isam.remove(input);
    if (removed) cout << "Registro eliminado" << endl;
    else cout << "No se encontro ningun registro con informacion de que jugo en la season " << input << endl;
    auto fin_contador = chrono::high_resolution_clock::now();
    cout << "Tiempo de ejecucion: " << chrono::duration_cast<chrono::milliseconds>(fin_contador - inicio_contador).count() << "ms" << endl;
    cout << "Lecturas en disco duro: " << contadorLecturaIndexfile + contadorLecturaDatafile << endl;
    cout << "Escrituras en disco duro: " << contadorEscrituraIndexfile + contadorEscrituraDatafile << endl;
}

void test10(){
    ISAM isam;
    isam.loadCSV("data/championStats.csv");
    int input;
    do{
        cout << "Ingresa la season en la que jugo [1 - 12]: ";
        cin >> input;
        if ((input <= 0) || (input >= 13)) cout << "Season no valida";
    } while (input <= 0);
    auto inicio_contador = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; i++){
        vector<string> rec_to_insert;
        rec_to_insert.emplace_back(to_string(input));
        rec_to_insert.emplace_back("Main");
        rec_to_insert.emplace_back("Fizz");
        rec_to_insert.emplace_back("4");
        rec_to_insert.emplace_back("5.0");
        rec_to_insert.emplace_back("");
        rec_to_insert.emplace_back("4");
        rec_to_insert.emplace_back("2.0");
        rec_to_insert.emplace_back("3");
        rec_to_insert.emplace_back("1");
        rec_to_insert.emplace_back("75.0");
        rec_to_insert.emplace_back("2.5");
        rec_to_insert.emplace_back("1.25");
        rec_to_insert.emplace_back("4.0");
        rec_to_insert.emplace_back("5.2");
        rec_to_insert.emplace_back("275.25");
        rec_to_insert.emplace_back("7.86");
        rec_to_insert.emplace_back("13.2");
        rec_to_insert.emplace_back("375.0");
        rec_to_insert.emplace_back("");
        rec_to_insert.emplace_back("");
        rec_to_insert.emplace_back("76.5");
        rec_to_insert.emplace_back("29.4");
        rec_to_insert.emplace_back("20.6");

        Record record;
        record.loadRecord(rec_to_insert);
        isam.insert(record);
    }
    auto fin_contador = chrono::high_resolution_clock::now();
    cout << "Tiempo de ejecucion 10 inserciones: " << chrono::duration_cast<chrono::milliseconds>(fin_contador - inicio_contador).count() << " ms" << endl;
    cout << "Lecturas en disco duro: " << contadorLecturaIndexfile + contadorLecturaDatafile << endl;
    cout << "Escrituras en disco duro: " << contadorEscrituraIndexfile + contadorEscrituraDatafile << endl;
}

void test100(){
    ISAM isam;
    isam.loadCSV("data/championStats.csv");
    int input;
    do{
        cout << "Ingresa la season en la que jugo [1 - 12]: ";
        cin >> input;
        if ((input <= 0) || (input >= 13)) cout << "Season no valida";
    } while (input <= 0);
    auto inicio_contador = chrono::high_resolution_clock::now();
    for (int i = 1; i < 101; i++){
        vector<string> rec_to_insert;
        rec_to_insert.emplace_back(to_string(10));
        rec_to_insert.emplace_back("Main");
        rec_to_insert.emplace_back("Yasuo");
        rec_to_insert.emplace_back("4");
        rec_to_insert.emplace_back("5.0");
        rec_to_insert.emplace_back("");
        rec_to_insert.emplace_back("4");
        rec_to_insert.emplace_back("2.0");
        rec_to_insert.emplace_back("3");
        rec_to_insert.emplace_back("1");
        rec_to_insert.emplace_back("75.0");
        rec_to_insert.emplace_back("2.5");
        rec_to_insert.emplace_back("1.25");
        rec_to_insert.emplace_back("4.0");
        rec_to_insert.emplace_back("5.2");
        rec_to_insert.emplace_back("275.25");
        rec_to_insert.emplace_back("7.86");
        rec_to_insert.emplace_back("13.2");
        rec_to_insert.emplace_back("375.0");
        rec_to_insert.emplace_back("");
        rec_to_insert.emplace_back("");
        rec_to_insert.emplace_back("76.5");
        rec_to_insert.emplace_back("29.4");
        rec_to_insert.emplace_back("20.6");

        Record record;
        record.loadRecord(rec_to_insert);
        isam.insert(record);
    }
    auto fin_contador = chrono::high_resolution_clock::now();
    cout << "Tiempo de ejecucion 100 inserciones: " << chrono::duration_cast<chrono::milliseconds>(fin_contador - inicio_contador).count() << " ms" << endl;
    cout << "Lecturas en disco duro: " << contadorLecturaIndexfile + contadorLecturaDatafile << endl;
    cout << "Escrituras en disco duro: " << contadorEscrituraIndexfile + contadorEscrituraDatafile << endl;
}

void test1000(){
    ISAM isam;
    isam.loadCSV("data/championStats.csv");
    int input;
    do{
        cout << "Ingresa la season en la que jugo [1 - 12]: ";
        cin >> input;
        if ((input <= 0) || (input >= 13)) cout << "Season no valida";
    } while (input <= 0);
    auto inicio_contador = chrono::high_resolution_clock::now();
    for (int i = 1; i < 1001; i++){
        vector<string> rec_to_insert;
        rec_to_insert.emplace_back(to_string(10));
        rec_to_insert.emplace_back("Main");
        rec_to_insert.emplace_back("Yasuo");
        rec_to_insert.emplace_back("4");
        rec_to_insert.emplace_back("5.0");
        rec_to_insert.emplace_back("");
        rec_to_insert.emplace_back("4");
        rec_to_insert.emplace_back("2.0");
        rec_to_insert.emplace_back("3");
        rec_to_insert.emplace_back("1");
        rec_to_insert.emplace_back("75.0");
        rec_to_insert.emplace_back("2.5");
        rec_to_insert.emplace_back("1.25");
        rec_to_insert.emplace_back("4.0");
        rec_to_insert.emplace_back("5.2");
        rec_to_insert.emplace_back("275.25");
        rec_to_insert.emplace_back("7.86");
        rec_to_insert.emplace_back("13.2");
        rec_to_insert.emplace_back("375.0");
        rec_to_insert.emplace_back("");
        rec_to_insert.emplace_back("");
        rec_to_insert.emplace_back("76.5");
        rec_to_insert.emplace_back("29.4");
        rec_to_insert.emplace_back("20.6");

        Record record;
        record.loadRecord(rec_to_insert);
        isam.insert(record);
    }
    auto fin_contador = chrono::high_resolution_clock::now();
    cout << "Tiempo de ejecucion 1000 inserciones: " << chrono::duration_cast<chrono::milliseconds>(fin_contador - inicio_contador).count() << " ms" << endl;
    cout << "Lecturas en disco duro: " << contadorLecturaIndexfile + contadorLecturaDatafile << endl;
    cout << "Escrituras en disco duro: " << contadorEscrituraIndexfile + contadorEscrituraDatafile << endl;
}

int main(){
    //test_insert();
    //test_search();
    //test_search_in_range();
    //test_remove();
    //test10();
    //test100();
    test1000();
}