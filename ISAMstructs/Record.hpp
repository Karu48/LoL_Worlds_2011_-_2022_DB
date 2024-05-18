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

template <typename T>
vector<string> getFields(const T&);

template <typename T>
void setFields(T&, const vector<string>&);

// Especializaciones para ChampionStats, MatchStats, y PlayerStats

template <>
vector<string> getFields(const ChampionStats& cs) {
    return {
        to_string(cs.season),
        cs.event,
        cs.champion,
        to_string(cs.gamesContests),
        to_string(cs.pickBanRatio),
        to_string(cs.bannedGames),
        to_string(cs.playedGames),
        to_string(cs.playedByNumberOfPlayers),
        to_string(cs.wins),
        to_string(cs.losses),
        to_string(cs.winRate),
        to_string(cs.kills),
        to_string(cs.deaths),
        to_string(cs.assists),
        to_string(cs.kdaRatio),
        to_string(cs.CS),
        to_string(cs.CSmin),
        to_string(cs.gold),
        to_string(cs.goldMin),
        to_string(cs.damage),
        to_string(cs.damageMin),
        to_string(cs.KP),
        to_string(cs.killShare),
        to_string(cs.goldShare)
    };
}

template <>
void setFields(ChampionStats& cs, const vector<string>& fields) {
    int index = 0;
    cs.season = stoi(fields[index++]);
    strncpy(cs.event, fields[index++].c_str(), sizeof(cs.event) - 1);
    strncpy(cs.champion, fields[index++].c_str(), sizeof(cs.champion) - 1);
    cs.gamesContests = stoi(fields[index++]);
    cs.pickBanRatio = stof(fields[index++]);
    cs.bannedGames = stoi(fields[index++]);
    cs.playedGames = stoi(fields[index++]);
    cs.playedByNumberOfPlayers = stoi(fields[index++]);
    cs.wins = stoi(fields[index++]);
    cs.losses = stoi(fields[index++]);
    cs.winRate = stof(fields[index++]);
    cs.kills = stoi(fields[index++]);
    cs.deaths = stoi(fields[index++]);
    cs.assists = stoi(fields[index++]);
    cs.kdaRatio = stof(fields[index++]);
    cs.CS = stoi(fields[index++]);
    cs.CSmin = stof(fields[index++]);
    cs.gold = stoi(fields[index++]);
    cs.goldMin = stof(fields[index++]);
    cs.damage = stoi(fields[index++]);
    cs.damageMin = stof(fields[index++]);
    cs.KP = stof(fields[index++]);
    cs.killShare = stof(fields[index++]);
    cs.goldShare = stof(fields[index++]);
}

template <>
vector<string> getFields(const MatchStats& ms) {
    return {
        to_string(ms.season),
        ms.date,
        ms.event,
        to_string(ms.patch),
        ms.blue_team,
        ms.red_team,
        ms.winner,
        ms.ban_1_blue_team,
        ms.ban_2_blue_team,
        ms.ban_3_blue_team,
        ms.ban_4_blue_team,
        ms.ban_5_blue_team,
        ms.ban_1_red_team,
        ms.ban_2_red_team,
        ms.ban_3_red_team,
        ms.ban_4_red_team,
        ms.ban_5_red_team,
        ms.pick_1_blue_team,
        ms.pick_2_blue_team,
        ms.pick_3_blue_team,
        ms.pick_4_blue_team,
        ms.pick_5_blue_team,
        ms.pick_1_red_team,
        ms.pick_2_red_team,
        ms.pick_3_red_team,
        ms.pick_4_red_team,
        ms.pick_5_red_team,
        ms.top_blue_team,
        ms.jungler_blue_team,
        ms.mid_blue_team,
        ms.adc_blue_team,
        ms.support_blue_team,
        ms.top_red_team,
        ms.jungler_red_team,
        ms.mid_red_team,
        ms.adc_red_team,
        ms.support_red_team
    };
}

template <>
void setFields(MatchStats& ms, const vector<string>& fields) {
    int index = 0;
    ms.season = stoi(fields[index++]);
    strncpy(ms.date, fields[index++].c_str(), sizeof(ms.date) - 1);
    strncpy(ms.event, fields[index++].c_str(), sizeof(ms.event) - 1);
    ms.patch = stof(fields[index++]);
    strncpy(ms.blue_team, fields[index++].c_str(), sizeof(ms.blue_team) - 1);
    strncpy(ms.red_team, fields[index++].c_str(), sizeof(ms.red_team) - 1);
    strncpy(ms.winner, fields[index++].c_str(), sizeof(ms.winner) - 1);
    strncpy(ms.ban_1_blue_team, fields[index++].c_str(), sizeof(ms.ban_1_blue_team) - 1);
    strncpy(ms.ban_2_blue_team, fields[index++].c_str(), sizeof(ms.ban_2_blue_team) - 1);
    strncpy(ms.ban_3_blue_team, fields[index++].c_str(), sizeof(ms.ban_3_blue_team) - 1);
    strncpy(ms.ban_4_blue_team, fields[index++].c_str(), sizeof(ms.ban_4_blue_team) - 1);
    strncpy(ms.ban_5_blue_team, fields[index++].c_str(), sizeof(ms.ban_5_blue_team) - 1);
    strncpy(ms.ban_1_red_team, fields[index++].c_str(), sizeof(ms.ban_1_red_team) - 1);
    strncpy(ms.ban_2_red_team, fields[index++].c_str(), sizeof(ms.ban_2_red_team) - 1);
    strncpy(ms.ban_3_red_team, fields[index++].c_str(), sizeof(ms.ban_3_red_team) - 1);
    strncpy(ms.ban_4_red_team, fields[index++].c_str(), sizeof(ms.ban_4_red_team) - 1);
    strncpy(ms.ban_5_red_team, fields[index++].c_str(), sizeof(ms.ban_5_red_team) - 1);
    strncpy(ms.pick_1_blue_team, fields[index++].c_str(), sizeof(ms.pick_1_blue_team) - 1);
    strncpy(ms.pick_2_blue_team, fields[index++].c_str(), sizeof(ms.pick_2_blue_team) - 1);
    strncpy(ms.pick_3_blue_team, fields[index++].c_str(), sizeof(ms.pick_3_blue_team) - 1);
    strncpy(ms.pick_4_blue_team, fields[index++].c_str(), sizeof(ms.pick_4_blue_team) - 1);
    strncpy(ms.pick_5_blue_team, fields[index++].c_str(), sizeof(ms.pick_5_blue_team) - 1);
    strncpy(ms.pick_1_red_team, fields[index++].c_str(), sizeof(ms.pick_1_red_team) - 1);
    strncpy(ms.pick_2_red_team, fields[index++].c_str(), sizeof(ms.pick_2_red_team) - 1);
    strncpy(ms.pick_3_red_team, fields[index++].c_str(), sizeof(ms.pick_3_red_team) - 1);
    strncpy(ms.pick_4_red_team, fields[index++].c_str(), sizeof(ms.pick_4_red_team) - 1);
    strncpy(ms.pick_5_red_team, fields[index++].c_str(), sizeof(ms.pick_5_red_team) - 1);
    strncpy(ms.top_blue_team, fields[index++].c_str(), sizeof(ms.top_blue_team) - 1);
    strncpy(ms.jungler_blue_team, fields[index++].c_str(), sizeof(ms.jungler_blue_team) - 1);
    strncpy(ms.mid_blue_team, fields[index++].c_str(), sizeof(ms.mid_blue_team) - 1);
    strncpy(ms.adc_blue_team, fields[index++].c_str(), sizeof(ms.adc_blue_team) - 1);
    strncpy(ms.support_blue_team, fields[index++].c_str(), sizeof(ms.support_blue_team) - 1);
    strncpy(ms.top_red_team, fields[index++].c_str(), sizeof(ms.top_red_team) - 1);
    strncpy(ms.jungler_red_team, fields[index++].c_str(), sizeof(ms.jungler_red_team) - 1);
    strncpy(ms.mid_red_team, fields[index++].c_str(), sizeof(ms.mid_red_team) - 1);
    strncpy(ms.adc_red_team, fields[index++].c_str(), sizeof(ms.adc_red_team) - 1);
    strncpy(ms.support_red_team, fields[index++].c_str(), sizeof(ms.support_red_team) - 1);
}

template <>
vector<string> getFields(const PlayerStats& ps) {
    return {
        to_string(ps.season),
        ps.event,
        ps.team,
        ps.player,
        to_string(ps.games_played),
        to_string(ps.wins),
        to_string(ps.loses),
        to_string(ps.win_rate),
        to_string(ps.kills),
        to_string(ps.deaths),
        to_string(ps.assists),
        to_string(ps.kill_death_assist_ratio),
        to_string(ps.creep_score),
        to_string(ps.cs_min),
        to_string(ps.gold),
        to_string(ps.gold_min),
        to_string(ps.damage),
        to_string(ps.damage_min),
        to_string(ps.kill_participation),
        to_string(ps.kill_share),
        to_string(ps.gold_share)
    };
}

template <>
void setFields(PlayerStats& ps, const vector<string>& fields) {
    int index = 0;
    ps.season = stoi(fields[index++]);
    strncpy(ps.event, fields[index++].c_str(), sizeof(ps.event) - 1);
    strncpy(ps.team, fields[index++].c_str(), sizeof(ps.team) - 1);
    strncpy(ps.player, fields[index++].c_str(), sizeof(ps.player) - 1);
    ps.games_played = stoi(fields[index++]);
    ps.wins = stoi(fields[index++]);
    ps.loses = stoi(fields[index++]);
    ps.win_rate = stof(fields[index++]);
    ps.kills = stoi(fields[index++]);
    ps.deaths = stoi(fields[index++]);
    ps.assists = stoi(fields[index++]);
    ps.kill_death_assist_ratio = stof(fields[index++]);
    ps.creep_score = stof(fields[index++]);
    ps.cs_min = stof(fields[index++]);
    ps.gold = stof(fields[index++]);
    ps.gold_min = stof(fields[index++]);
    ps.damage = stoi(fields[index++]);
    ps.damage_min = stof(fields[index++]);
    ps.kill_participation = stof(fields[index++]);
    ps.kill_share = stof(fields[index++]);
    ps.gold_share = stof(fields[index++]);
}

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