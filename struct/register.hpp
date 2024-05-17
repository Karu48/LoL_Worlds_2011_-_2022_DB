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
};