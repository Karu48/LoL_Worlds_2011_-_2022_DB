#pragma once
#include <iostream>
#include <variant>
#include <cstring>

struct ChampionStats{
    int key;
    int season;
    char event[7];
    char champion[15];
    int gamesContests;
    float pickBanRatio;
    int bannedGames;
    int playedGames;
    int playedByNumberOfPlayers;
    int wins;
    int losses;
    float winRate;
    int kills;
    int deaths;
    int assists;
    float kdaRatio;
    int CS;
    float CSmin;
    int gold;
    float goldMin;
    int damage;
    float damageMin;
    float KP;
    float killShare;
    float goldShare;

    ChampionStats(string data, string k){
        
        if (k == "season") key = 0;
        else if (k == "event") key = 1;
        else if (k == "champion") key = 2;
        else if (k == "gamesContests") key = 3;
        else if (k == "pickBanRatio") key = 4;
        else if (k == "bannedGames") key = 5;
        else if (k == "playedGames") key = 6;
        else if (k == "playedByNumberOfPlayers") key = 7;
        else if (k == "wins") key = 8;
        else if (k == "losses") key = 9;
        else if (k == "winRate") key = 10;
        else if (k == "kills") key = 11;
        else if (k == "deaths") key = 12;
        else if (k == "assists") key = 13;
        else if (k == "kdaRatio") key = 14;
        else if (k == "CS") key = 15;
        else if (k == "CSmin") key = 16;
        else if (k == "gold") key = 17;
        else if (k == "goldMin") key = 18;
        else if (k == "damage") key = 19;
        else if (k == "damageMin") key = 20;
        else if (k == "KP") key = 21;
        else if (k == "killShare") key = 22;
        else if (k == "goldShare") key = 23;
        else key = -1;

        string temp;
        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        if (temp == ""){
            season = -1;
        } else {
            season = stoi(temp);
        }
        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);

        char e[10] = "";
        for (int i = 0; i < temp.size(); i++){
            e[i] = temp[i];
        }

        strncpy(event, e, sizeof(event) - 1);
        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        char c[15] = "";

        for (int i = 0; i < temp.size(); i++){
            c[i] = temp[i];
        }

        strncpy(champion, c, sizeof(champion) - 1);
        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        if (temp == ""){
            gamesContests = -1;
        } else {
            gamesContests = stoi(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        if (temp == ""){
            pickBanRatio = -1;
        } else {
            pickBanRatio = stof(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        if (temp == ""){
            bannedGames = -1;
        } else {
            bannedGames = stoi(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        if (temp == ""){
            playedGames = -1;
        } else {
            playedGames = stoi(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        if (temp == ""){
            playedByNumberOfPlayers = -1;
        } else {
            playedByNumberOfPlayers = stoi(temp);
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
            losses = -1;
        } else {
            losses = stoi(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        if (temp == ""){
            winRate = -1;
        } else {
            winRate = stof(temp);
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
            kdaRatio = -1;
        } else {
            kdaRatio = stof(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        if (temp == ""){
            CS = -1;
        } else {
            CS = stoi(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        if (temp == ""){
            CSmin = -1;
        } else {
            CSmin = stof(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        if (temp == ""){
            gold = -1;
        } else {
            gold = stoi(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        if (temp == ""){
            goldMin = -1;
        } else {
            goldMin = stof(temp);
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
            damageMin = -1;
        } else {
            damageMin = stof(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1); 
        if (temp == ""){
            KP = -1;
        } else {
            KP = stof(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1); 
        if (temp == ""){
            killShare = -1;
        } else {
            killShare = stof(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1); 
        if (temp == ""){
            goldShare = -1;
        } else {
            goldShare = stof(temp);
        }
    }

    variant<int, float, string>getKey() const {
        switch (key){
            case 0:
                return season;
            case 1:
                return event;
            case 2:
                return champion;
            case 3:
                return gamesContests;
            case 4:
                return pickBanRatio;
            case 5:
                return bannedGames;
            case 6:
                return playedGames;
            case 7:
                return playedByNumberOfPlayers;
            case 8:
                return wins;
            case 9:
                return losses;
            case 10:
                return winRate;
            case 11:
                return kills;
            case 12:
                return deaths;
            case 13:
                return assists;
            case 14:
                return kdaRatio;
            case 15:
                return CS;
            case 16:
                return CSmin;
            case 17:
                return gold;
            case 18:
                return goldMin;
            case 19:
                return damage;
            case 20:
                return damageMin;
            case 21:
                return KP;
            case 22:
                return killShare;
            case 23:
                return goldShare;
            default:
                return -1;
        }
    }

    void print(){
        cout << "Season: " << season << endl;
        cout << "Event: " << event << endl;
        cout << "Champion: " << champion << endl;
        cout << "Games Contests: " << gamesContests << endl;
        cout << "Pick/Ban Ratio: " << pickBanRatio << endl;
        cout << "Banned Games: " << bannedGames << endl;
        cout << "Played Games: " << playedGames << endl;
        cout << "Played By Number Of Players: " << playedByNumberOfPlayers << endl;
        cout << "Wins: " << wins << endl;
        cout << "Losses: " << losses << endl;
        cout << "Win Rate: " << winRate << endl;
        cout << "Kills: " << kills << endl;
        cout << "Deaths: " << deaths << endl;
        cout << "Assists: " << assists << endl;
        cout << "KDA Ratio: " << kdaRatio << endl;
        cout << "CS: " << CS << endl;
        cout << "CS/min: " << CSmin << endl;
        cout << "Gold: " << gold << endl;
        cout << "Gold/min: " << goldMin << endl;
        cout << "Damage: " << damage << endl;
        cout << "Damage/min: " << damageMin << endl;
        cout << "KP: " << KP << endl;
        cout << "Kill Share: " << killShare << endl;
        cout << "Gold Share: " << goldShare << endl;
    }
};

