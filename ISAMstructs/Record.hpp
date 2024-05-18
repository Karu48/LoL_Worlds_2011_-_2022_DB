#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <utility>
#include "buffer.hpp"
#include "../struct/championStats.hpp"
#include "../struct/matchStats.hpp"
#include "../struct/playerStats.hpp"

using namespace std;
using TCSV = variant<ChampionStats, MatchStats, PlayerStats>;

struct Record {
public:
    TCSV csv; // variant<ChampionStats, MatchStats, PlayerStats> data;
    long initializer;
    vector<string> pre_record; // Guarda los datos de un record

    Record(): initializer(0), csv(ChampionStats("","")) {}

    // funciona como loadRecord pero con un solo string
    Record(string data, string keyCSV, string type): initializer(0), csv(ChampionStats("","")){
        if (type == "champion") {
            csv = ChampionStats(data, keyCSV);
        } else if (type == "match") {
            MatchStats(data, keyCSV);
            csv = MatchStats(data, keyCSV);
        } else if (type == "player") {
            PlayerStats(data, keyCSV);
            csv = PlayerStats(data, keyCSV);
        }
    }

    // Empaquetar los datos de un record en un buffer
    void pack(Buffer &buffer) {
        buffer.clear();
        for (const auto &field : pre_record) {
            buffer.pack(field.data());
        }
    }

    // Desempaquetar los datos de un buffer en un record
    void unpack(Buffer &buffer) {
        char* temp = new char[buffer.get_max_bytes()];
        if (pre_record.empty()) {
            while (buffer.unpack(temp)) {
                string field_str(temp);
                pre_record.push_back(field_str);
            }
        } else {
            for (auto &field : pre_record) {
                if (buffer.unpack(temp)) {
                    string field_str(temp);
                    field = field_str;
                }
                else throw runtime_error("No se pudo desempaquetar el buffer");
            }
        }
        delete[] temp;
    }

    // Imprimir los datos de un record campo por campo
    void print() {
        for (auto &field : pre_record) cout << field << " ";
        cout << endl;
    }
    

    // Cargar los datos de un record
    void loadRecord(vector<string> new_data) {
        pre_record = std::move(new_data);
    }

    //int get_key() const {return stoi(pre_record[0]);} // primary key del record, columna 0
    

    variant<int,float,string> getVariantPrimaryKey() const{
        if (csv.index() == 0) return get<ChampionStats>(csv).getKey();
        else if (csv.index() == 1) return get<MatchStats>(csv).getKey();
        else if (csv.index() == 2) return get<PlayerStats>(csv).getKey();
        else return -1;
    }

    // Imprimir los datos de un registro
    void print_variant() {
        visit([](auto&& arg) {
            using T = decay_t<decltype(arg)>;
            arg.print();
        }, csv);
    }
};