#include "ISAMstructs/ISAM.h"
#include <chrono>
#include <vector>

using namespace std;

void test_insert() {
    ISAM isam;
    isam.loadCSV("data/championStats.csv");
    int input;
    do{
        cout << "Ingresa la season en la que jugo: ";
        cin >> input;
        if (input <= 0) cout << "Season no valida";
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
    cout << "Tiempo de ejecucion: " << chrono::duration_cast<chrono::microseconds>(fin_contador - inicio_contador).count() << "us" << endl;
    cout << "Accesos a memoria secundaria" << endl;
    cout << "Lecturas: " << contadorLecturaIndexfile + contadorLecturaDatafile << endl;
    cout << "Escrituras: " << contadorEscrituraIndexfile + contadorEscrituraDatafile << endl;
}

void test_search(){
    ISAM isam;
    isam.loadCSV("data/championStats.csv");
    int input;
    do{
        cout << "Ingresa la season en la que jugo: ";
        cin >> input;
        if (input <= 0) cout << "Season no valida";
    } while (input <= 0);

    auto inicio_contador = chrono::high_resolution_clock::now();
    auto dataRecord = isam.search(input);
    if(dataRecord.has_value()) dataRecord->print();
    else cout << "No se encontro ningun registro con informacion de que jugo en la season " << input << endl;
    auto fin_contador = chrono::high_resolution_clock::now();
    cout << "Tiempo de ejecucion: " << chrono::duration_cast<chrono::microseconds>(fin_contador - inicio_contador).count() << "us" << endl;
    // Reestablecer contadores
    contadorLecturaIndexfile = 0;
    contadorLecturaDatafile = 0;
    contadorEscrituraIndexfile = 0;
    contadorEscrituraDatafile = 0;
}

// Si el key se repite, solo muestra los ultimos registros del begin y uno solo del end
void test_search_in_range(){
    ISAM isam;
    isam.loadCSV("data/championStats.csv");
    int input1, input2;
    do{
        cout << "Ingresa el rango de temporadas a buscar [ingresa la primera, enter, y ingresa la segunda]: ";
        cin >> input1 >> input2;
        if (input1 <= 0 || input2 <= 0) cout << "Season no valida";
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
    cout << "Tiempo de ejecucion: " << chrono::duration_cast<chrono::microseconds>(fin_contador - inicio_contador).count() << "us" << endl;
}

void test_remove(){
    ISAM isam;
    isam.loadCSV("data/championStats.csv");
    int input;
    do{
        cout << "Ingresa la season en la que jugo: ";
        cin >> input;
        if (input <= 0) cout << "Season no valida";
    } while (input <= 0);

    auto inicio_contador = chrono::high_resolution_clock::now();
    bool removed = isam.remove(input);
    if (removed) cout << "Registro eliminado" << endl;
    else cout << "No se encontro ningun registro con informacion de que jugo en la season " << input << endl;
    auto fin_contador = chrono::high_resolution_clock::now();
    cout << "Tiempo de ejecucion: " << chrono::duration_cast<chrono::microseconds>(fin_contador - inicio_contador).count() << "us" << endl;
    cout << "Accesos a memoria secundaria" << endl;
    cout << "Lecturas: " << contadorLecturaIndexfile + contadorLecturaDatafile << endl;
    cout << "Escrituras: " << contadorEscrituraIndexfile + contadorEscrituraDatafile << endl;
}

int main()
{
    /*
  const std::string& csv =
    "Date,Open,High,Low,Close,Volume,Adj Close\n"
    "2017-02-24,64.529999,64.800003,64.139999,64.620003,21705200,64.620003\n"
    "2017-02-23,64.419998,64.730003,64.190002,64.620003,20235200,64.620003\n"
    "2017-02-22,64.330002,64.389999,64.050003,64.360001,19259700,64.360001\n"
    "2017-02-21,64.610001,64.949997,64.449997,64.489998,19384900,64.489998\n"
    "2017-02-17,64.470001,64.690002,64.300003,64.620003,21234600,64.620003\n"
    ;

  const std::string& csv2 =
    "season,event,champion,games_contests,pick_ban_ratio,banned_games,played_games,played_by_number_of_players,win,lose,win_rate,kills,deaths,assists,kill_death_assist_ratio,creep_score,cs/min,gold,gold/min,damage,damage/min,kill_participation,kill_share,gold_share\n"
    "3,Main,Nunu,27,96.4,9.0,1,6.0,1,6,66.7,1.6,2.6,8.1,3.63,90.1,2.46,9.4,256.0,,,,,\n"
    "1,Main,Alis,25,89.3,1.0,1,4.0,8,5,61.5,3.4,2.6,7.8,4.03,11.0,3.11,9.6,261.0,,,,,\n"
    "1,Main,Rumb,23,82.1,2.0,2,2.0,2,0,10.0,3.5,1.5,9.0,8.33,16.0,5.02,1.1,311.0,,,,,\n"
    "1,Main,Vlad,22,78.6,1.0,8,5.0,3,5,37.5,4.5,3.5,3.8,2.39,22.6,5.99,1.2,298.0,,,,,\n"
    "1,Main,Twis,22,78.6,1.0,4,2.0,2,2,50.0,2.0,4.5,5.5,1.67,20.5,5.43,1.4,299.0,,,,,\n"
    ;

    TEST DE RAPIDCSV
  std::stringstream sstream(csv2);
  rapidcsv::Document doc(sstream, rapidcsv::LabelParams(0, 0));

  std::vector<string> event = doc.GetColumn<string>("event"); // aca se puede cambiar el tipo de dato
  std::cout << "Read " << event.size() << " values." << std::endl;

  string champion = doc.GetCell<string>("champion", "3");
  std::cout << "champion " << champion << " on season 1." << std::endl;
  */

 /*
  rapidcsv::Document doc("data/championStats.csv", rapidcsv::LabelParams(0, 0));
    std::vector<string> event = doc.GetColumn<string>("event"); // aca se puede cambiar el tipo de dato
    std::cout << "Read " << event.size() << " values." << std::endl;

  string champion = doc.GetCell<string>("champion", "3");
  std::cout << "champion " << champion << " on season 3." << std::endl;
  */
    //ISAM isam;
    //isam.loadCSV("data/playerStats.csv");
    //isam.printIndex();
    //isam.printAll();
    //Record record;
    //vector<string> data = {"1", "Main", "Fizz", "4", "5.0", "", "4", "2.0", "3", "1", "75.0", "2.5", "1.25", "4.0", "5.2", "275.25", "7.86", "13.2", "375.0", "", "", "76.5", "29.4", "20.6"};
    //record.load_data(data);
    //record.print();
    //Record record2;
    //vector<string> data2 = {"12", "Main", "Yasuo", "4", "5.0", "", "4", "2.0", "3", "1", "75.0", "2.5", "1.25", "4.0", "5.2", "275.25", "7.86", "13.2", "375.0", "", "", "76.5", "29.4", "20.6"};
    //record2.load_data(data2);
    // Insercion:
    //isam.insert(record); // IT WORKS
    //isam.insert(record2); // IT WORKS

    /*
    // Search:
    optional<Record> record = isam.search(12);
    if (record.has_value()) {
        record.value().print();
    } else {
        cout << "Record not found" << endl;
    }
    */

    /* IT WORKS RETURN ONE VALUE RECORD
    auto dataRecord = isam.search(6);
    if(dataRecord.has_value()) dataRecord->print();
    else cout << "No se encontro ningun registro con que jugo en la season 6: " << endl;
    */
   
    /* IT WORKS RETURN SEASON PLAYES 1 TO 6 (NOT ALL 1 BUT OTHER SEASON YEP)
    auto records = isam.rangeSearch(1, 7);
    if(!records.empty()){
        for(auto &r : records){
            r.print();
        }
    } else {
        cout << "No records found" << endl;
    }
    */


    // Eliminacion: True => 1, False => 0
    //cout << isam.remove(1);

    //isam.printAll();

    test_insert();
    //test_search();
    //test_search_in_range();
    //test_remove();
    return 0;
}