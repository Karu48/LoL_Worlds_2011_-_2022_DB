#include <iostream>
#include <cstring>

using namespace std;

struct PlayerStats{
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
    int creep_score;
    float cs_min;
    int gold;
    float gold_min;
    int damage;
    float damage_min;
    float kill_participation;
    float kill_share;
    float gold_share;

    PlayerStats(string data) {
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
            p[i] = p[i];
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
            creep_score = stoi(temp);
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
            gold = stoi(temp);
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
};