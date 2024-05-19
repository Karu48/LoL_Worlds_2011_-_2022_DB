#pragma once
#include <variant>
#include "championStats.hpp"
#include "matchStats.hpp"
#include "playerStats.hpp"

using namespace std;

struct Register {    
    variant<ChampionStats, MatchStats, PlayerStats> data;

    Register() : data(ChampionStats("", "")) {}

    Register(string data, string k, string type) : data(ChampionStats("", "")) {
        if (type == "champion") {
            ChampionStats champ(data, k);
            this->data = champ;
        }
        else if (type == "match") {
            MatchStats match(data, k);
            this->data = match;
        } else if (type == "player") {
            PlayerStats player(data, k);
            this->data = player;
        }
    }

    bool operator ==(const Register &other) const {
        return data == other.data;
    }

    void setKey(variant<int, float, string> k, string type, string keyType) {
        if (type == "champion") {
            ChampionStats champ("", keyType);
            champ.setKey(k);
            data = champ;
        } else if (type == "match") {
            MatchStats match("", keyType);
            match.setKey(k);
            data = match;
        } else if (type == "player") {
            PlayerStats player("", keyType);
            player.setKey(k);
            data = player;
        }

    }

    void print(){
        if (data.index() == 0) {
            ChampionStats champ = get<ChampionStats>(data);
            champ.print();
        } else if (data.index() == 1) {
            MatchStats match = get<MatchStats>(data);
            match.print();
        } else if (data.index() == 2) {
            PlayerStats player = get<PlayerStats>(data);
            player.print();
        }
    }
};