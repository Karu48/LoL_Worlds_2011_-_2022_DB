#include <iostream>
#include <cstring>

using namespace std;

struct ChampionStats{
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

    ChampionStats(string data){
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

        char e[10];
        for (int i = 0; i < temp.size(); i++){
            e[i] = temp[i];
        }

        strncpy(event, e, sizeof(event) - 1);
        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        char c[15];

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

