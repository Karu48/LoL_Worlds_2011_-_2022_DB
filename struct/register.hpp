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
        if (type == "champion") this->data = ChampionStats(data, k);
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
};