#pragma once
#include <iostream>
#include <variant>
#include <cstring>

using namespace std;

struct PlayerStats{
    int key;
    int season;
    char event[7];
    char team[45];
    char player[15];
    int games_played;
    int wins;
    int loses;
    float win_rate;
    int kills;
    int deaths;
    int assists;
    float kill_death_assist_ratio;
    float creep_score;
    float cs_min;
    float gold;
    float gold_min;
    int damage;
    float damage_min;
    float kill_participation;
    float kill_share;
    float gold_share;

    PlayerStats(string data, string k) {
        // set key
        if (k == "season") key = 0;
        else if (k == "event") key = 1;
        else if (k == "team") key = 2;
        else if (k == "player") key = 3;
        else if (k == "games_played") key = 4;
        else if (k == "wins") key = 5;
        else if (k == "loses") key = 6;
        else if (k == "win_rate") key = 7;
        else if (k == "kills") key = 8;
        else if (k == "deaths") key = 9;
        else if (k == "assists") key = 10;
        else if (k == "kill_death_assist_ratio") key = 11;
        else if (k == "creep_score") key = 12;
        else if (k == "cs_min") key = 13;
        else if (k == "gold") key = 14;
        else if (k == "gold_min") key = 15;
        else if (k == "damage") key = 16;
        else if (k == "damage_min") key = 17;
        else if (k == "kill_participation") key = 18;
        else if (k == "kill_share") key = 19;
        else if (k == "gold_share") key = 20;
        else key = -1;

        // parse data
        string temp = "";
        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        if (temp == ""){
            season = -1;
        } else {
            season = stoi(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        char e[7] = "";
        for (int i = 0; i < temp.size(); i++){
            e[i] = temp[i];
        }
        strncpy(event, e, sizeof(event) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        char b[45] = "";
        for (int i = 0; i < temp.size(); i++){
            b[i] = temp[i];
        }
        strncpy(team, b, sizeof(team) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        char p[15] = "";
        for (int i = 0; i < temp.size(); i++){
            p[i] = temp[i];
        }
        strncpy(player, p, sizeof(player) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        if (temp == ""){
            games_played = -1;
        } else {
            games_played = stoi(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        if (temp == ""){
            wins = -1;
        } else {
            wins = stoi(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        if (temp == ""){
            loses = -1;
        } else {
            loses = stoi(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        if (temp == ""){
            win_rate = -1;
        } else {
            win_rate = stof(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        if (temp == ""){
            kills = -1;
        } else {
            kills = stoi(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        if (temp == ""){
            deaths = -1;
        } else {
            deaths = stoi(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        if (temp == ""){
            assists = -1;
        } else {
            assists = stoi(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1); 
        if (temp == ""){
            kill_death_assist_ratio = -1;
        } else {
            kill_death_assist_ratio = stof(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        if (temp == ""){
            creep_score = -1;
        } else {
            creep_score = stof(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1); 
        if (temp == ""){
            cs_min = -1;
        } else {
            cs_min = stof(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1); 
        if (temp == ""){
            gold = -1;
        } else {
            gold = stof(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1); 
        if (temp == ""){
            gold_min = -1;
        } else {
            gold_min = stof(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1); 
        if (temp == ""){
            damage = -1;
        } else {
            damage = stoi(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1); 
        if (temp == ""){
            damage_min = -1;
        } else {
            damage_min = stof(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1); 
        if (temp == ""){
            kill_participation = -1;
        } else {
            kill_participation = stof(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1); 
        if (temp == ""){
            kill_share = -1;
        } else {
            kill_share = stof(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1); 
        if (temp == ""){
            gold_share = -1;
        } else {
            gold_share = stof(temp);
        }
    }

    variant<int, float, string> getKey() const {
        if (key == 0) return season;
        else if (key == 1) return event;
        else if (key == 2) return team;
        else if (key == 3) return player;
        else if (key == 4) return games_played;
        else if (key == 5) return wins;
        else if (key == 6) return loses;
        else if (key == 7) return win_rate;
        else if (key == 8) return kills;
        else if (key == 9) return deaths;
        else if (key == 10) return assists;
        else if (key == 11) return kill_death_assist_ratio;
        else if (key == 12) return creep_score;
        else if (key == 13) return cs_min;
        else if (key == 14) return gold;
        else if (key == 15) return gold_min;
        else if (key == 16) return damage;
        else if (key == 17) return damage_min;
        else if (key == 18) return kill_participation;
        else if (key == 19) return kill_share;
        else if (key == 20) return gold_share;
        else return -1;
    }

    void print(){
        cout << "Season: " << season << endl;
        cout << "Event: " << event << endl;
        cout << "Team: " << team << endl;
        cout << "Player: " << player << endl;
        cout << "Games Played: " << games_played << endl;
        cout << "Wins: " << wins << endl;
        cout << "Loses: " << loses << endl;
        cout << "Win Rate: " << win_rate << endl;
        cout << "Kills: " << kills << endl;
        cout << "Deaths: " << deaths << endl;
        cout << "Assists: " << assists << endl;
        cout << "KDA: " << kill_death_assist_ratio << endl;
        cout << "Creep Score: " << creep_score << endl;
        cout << "CS/min: " << cs_min << endl;
        cout << "Gold: " << gold << endl;
        cout << "Gold/min: " << gold_min << endl;
        cout << "Damage: " << damage << endl;
        cout << "Damage/min: " << damage_min << endl;
        cout << "Kill Participation: " << kill_participation << endl;
        cout << "Kill Share: " << kill_share << endl;
        cout << "Gold Share: " << gold_share << endl;
    }

    bool operator==(const PlayerStats &other) const {
        return season == other.season && strcmp(event, other.event) == 0 && strcmp(team, other.team) == 0 && strcmp(player, other.player) == 0 && games_played == other.games_played && wins == other.wins && loses == other.loses && win_rate == other.win_rate && kills == other.kills && deaths == other.deaths && assists == other.assists && kill_death_assist_ratio == other.kill_death_assist_ratio && creep_score == other.creep_score && cs_min == other.cs_min && gold == other.gold && gold_min == other.gold_min && damage == other.damage && damage_min == other.damage_min && kill_participation == other.kill_participation && kill_share == other.kill_share && gold_share == other.gold_share;
    }

    void setKey(variant<int, float, string> k){
        if (key == 0) season = get<int>(k);
        else if (key == 1) strncpy(event, get<string>(k).c_str(), sizeof(event) - 1);
        else if (key == 2) strncpy(team, get<string>(k).c_str(), sizeof(team) - 1);
        else if (key == 3) strncpy(player, get<string>(k).c_str(), sizeof(player) - 1);
        else if (key == 4) games_played = get<int>(k);
        else if (key == 5) wins = get<int>(k);
        else if (key == 6) loses = get<int>(k);
        else if (key == 7) win_rate = get<float>(k);
        else if (key == 8) kills = get<int>(k);
        else if (key == 9) deaths = get<int>(k);
        else if (key == 10) assists = get<int>(k);
        else if (key == 11) kill_death_assist_ratio = get<float>(k);
        else if (key == 12) creep_score = get<float>(k);
        else if (key == 13) cs_min = get<float>(k);
        else if (key == 14) gold = get<float>(k);
        else if (key == 15) gold_min = get<float>(k);
        else if (key == 16) damage = get<int>(k);
        else if (key == 17) damage_min = get<float>(k);
        else if (key == 18) kill_participation = get<float>(k);
        else if (key == 19) kill_share = get<float>(k);
        else if (key == 20) gold_share = get<float>(k);
    }

    // Getters for each attribute
    int getSeason() const { return season; }
    string getEvent() const { return event; }
    string getTeam() const { return team; }
    string getPlayer() const { return player; }
    int getGamesPlayed() const { return games_played; }
    int getWins() const { return wins; }
    int getLoses() const { return loses; }
    float getWinRate() const { return win_rate; }
    int getKills() const { return kills; }
    int getDeaths() const { return deaths; }
    int getAssists() const { return assists; }
    float getKillDeathAssistRatio() const { return kill_death_assist_ratio; }
    float getCreepScore() const { return creep_score; }
    float getCSMin() const { return cs_min; }
    float getGold() const { return gold; }
    float getGoldMin() const { return gold_min; }
    int getDamage() const { return damage; }
    float getDamageMin() const { return damage_min; }
    float getKillParticipation() const { return kill_participation; }
    float getKillShare() const { return kill_share; }
    float getGoldShare() const { return gold_share; }
};