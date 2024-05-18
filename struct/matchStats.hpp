#pragma once
#include <iostream>
#include <variant>
#include <cstring>

using namespace std;

struct MatchStats{
    int key;
    int season;
    char date[10];
    char event[7];
    float patch;
    char blue_team[45];
    char red_team[45];
    char winner[45];
    char ban_1_blue_team[15];
    char ban_2_blue_team[15];
    char ban_3_blue_team[15];
    char ban_4_blue_team[15];
    char ban_5_blue_team[15];
    char ban_1_red_team[15];
    char ban_2_red_team[15];
    char ban_3_red_team[15];
    char ban_4_red_team[15];
    char ban_5_red_team[15];
    char pick_1_blue_team[15];
    char pick_2_blue_team[15];
    char pick_3_blue_team[15];
    char pick_4_blue_team[15];
    char pick_5_blue_team[15];
    char pick_1_red_team[15];
    char pick_2_red_team[15];
    char pick_3_red_team[15];
    char pick_4_red_team[15];
    char pick_5_red_team[15];
    char top_blue_team[15];
    char jungler_blue_team[15];
    char mid_blue_team[15];
    char adc_blue_team[15];
    char support_blue_team[15];
    char top_red_team[15];
    char jungler_red_team[15];
    char mid_red_team[15];
    char adc_red_team[15];
    char support_red_team[15];

    MatchStats(string data, string k){
        // Define key
        if (k == "season") key = 0;
        else if (k == "date") key = 1;
        else if (k == "event") key = 2;
        else if (k == "patch") key = 3;
        else if (k == "blue_team") key = 4;
        else if (k == "red_team") key = 5;
        else if (k == "winner") key = 6;
        else if (k == "ban_1_blue_team") key = 7;
        else if (k == "ban_2_blue_team") key = 8;
        else if (k == "ban_3_blue_team") key = 9;
        else if (k == "ban_4_blue_team") key = 10;
        else if (k == "ban_5_blue_team") key = 11;
        else if (k == "ban_1_red_team") key = 12;
        else if (k == "ban_2_red_team") key = 13;
        else if (k == "ban_3_red_team") key = 14;
        else if (k == "ban_4_red_team") key = 15;
        else if (k == "ban_5_red_team") key = 16;
        else if (k == "pick_1_blue_team") key = 17;
        else if (k == "pick_2_blue_team") key = 18;
        else if (k == "pick_3_blue_team") key = 19;
        else if (k == "pick_4_blue_team") key = 20;
        else if (k == "pick_5_blue_team") key = 21;
        else if (k == "pick_1_red_team") key = 22;
        else if (k == "pick_2_red_team") key = 23;
        else if (k == "pick_3_red_team") key = 24;
        else if (k == "pick_4_red_team") key = 25;
        else if (k == "pick_5_red_team") key = 26;
        else if (k == "top_blue_team") key = 27;
        else if (k == "jungler_blue_team") key = 28;
        else if (k == "mid_blue_team") key = 29;
        else if (k == "bot_blue_team") key = 30;
        else if (k == "support_blue_team") key = 31;
        else if (k == "top_red_team") key = 32;
        else if (k == "jungler_red_team") key = 33;
        else if (k == "mid_red_team") key = 34;
        else if (k == "bot_red_team") key = 35;
        else if (k == "support_red_team") key = 36;
        else key = -1;

        // Parse data
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
        char d[10] = "";
        for (int i = 0; i < temp.size(); i++){
            d[i] = temp[i];
        }
        strncpy(date, d, sizeof(date) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        char e[7] = "";
        for (int i = 0; i < temp.size(); i++){
            e[i] = temp[i];
        }
        strncpy(event, e, sizeof(event) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        if (temp == ""){
            patch = -1;
        } else {
            patch = stof(temp);
        }

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        char b[45] = "";
        for (int i = 0; i < temp.size(); i++){
            b[i] = temp[i];
        }
        strncpy(blue_team, b, sizeof(blue_team) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        strncpy(winner, b, sizeof(winner) - 1);
        for (int i = 0; i < temp.size(); i++){
            b[i] = temp[i];
        }
        strncpy(red_team, b, sizeof(red_team) - 1);
        
        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(b, 0, sizeof(b));
        for (int i = 0; i < temp.size(); i++){
            b[i] = temp[i];
        }
        strncpy(winner, b, sizeof(winner) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        char champ[15] = "";
        for (int i = 0; i < temp.size(); i++){
            champ[i] = temp[i];
        }
        strncpy(ban_1_blue_team, champ, sizeof(ban_1_blue_team) - 1);


        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(champ, 0, sizeof(champ));
        for (int i = 0; i < temp.size(); i++){
            champ[i] = temp[i];
        }
        strncpy(ban_2_blue_team, champ, sizeof(ban_2_blue_team) - 1);
        

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(champ, 0, sizeof(champ));
        for (int i = 0; i < temp.size(); i++){
            champ[i] = temp[i];
        }
        strncpy(ban_3_blue_team, champ, sizeof(ban_3_blue_team) - 1);
    
        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(champ, 0, sizeof(champ));
        for (int i = 0; i < temp.size(); i++){
            champ[i] = temp[i];
        }
        strncpy(ban_4_blue_team, champ, sizeof(ban_4_blue_team) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(champ, 0, sizeof(champ));
        for (int i = 0; i < temp.size(); i++){
            champ[i] = temp[i];
        }
        strncpy(ban_5_blue_team, champ, sizeof(ban_5_blue_team) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(champ, 0, sizeof(champ));
        for (int i = 0; i < temp.size(); i++){
            champ[i] = temp[i];
        }
        strncpy(ban_1_red_team, champ, sizeof(ban_1_red_team) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(champ, 0, sizeof(champ));
        for (int i = 0; i < temp.size(); i++){
            champ[i] = temp[i];
        }
        strncpy(ban_2_red_team, champ, sizeof(ban_2_red_team) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(champ, 0, sizeof(champ));
        for (int i = 0; i < temp.size(); i++){
            champ[i] = temp[i];
        }
        strncpy(ban_3_red_team, champ, sizeof(ban_3_red_team) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(champ, 0, sizeof(champ));
        for (int i = 0; i < temp.size(); i++){
            champ[i] = temp[i];
        }
        strncpy(ban_4_red_team, champ, sizeof(ban_4_red_team) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(champ, 0, sizeof(champ));
        for (int i = 0; i < temp.size(); i++){
            champ[i] = temp[i];
        }
        strncpy(ban_5_red_team, champ, sizeof(ban_5_red_team) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(champ, 0, sizeof(champ));
        for (int i = 0; i < temp.size(); i++){
            champ[i] = temp[i];
        }
        strncpy(pick_1_blue_team, champ, sizeof(pick_1_blue_team) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(champ, 0, sizeof(champ));
        for (int i = 0; i < temp.size(); i++){
            champ[i] = temp[i];
        }
        strncpy(pick_2_blue_team, champ, sizeof(pick_2_blue_team) - 1); 

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(champ, 0, sizeof(champ));
        for (int i = 0; i < temp.size(); i++){
            champ[i] = temp[i];
        }
        strncpy(pick_3_blue_team, champ, sizeof(pick_3_blue_team) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(champ, 0, sizeof(champ));
        for (int i = 0; i < temp.size(); i++){
            champ[i] = temp[i];
        }
        strncpy(pick_4_blue_team, champ, sizeof(pick_4_blue_team) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(champ, 0, sizeof(champ));
        for (int i = 0; i < temp.size(); i++){
            champ[i] = temp[i];
        }
        strncpy(pick_5_blue_team, champ, sizeof(pick_5_blue_team) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(champ, 0, sizeof(champ));
        for (int i = 0; i < temp.size(); i++){
            champ[i] = temp[i];
        }
        strncpy(pick_1_red_team, champ, sizeof(pick_1_red_team) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(champ, 0, sizeof(champ));
        for (int i = 0; i < temp.size(); i++){
            champ[i] = temp[i];
        }
        strncpy(pick_2_red_team, champ, sizeof(pick_2_red_team) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(champ, 0, sizeof(champ));
        for (int i = 0; i < temp.size(); i++){
            champ[i] = temp[i];
        }
        strncpy(pick_3_red_team, champ, sizeof(pick_3_red_team) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(champ, 0, sizeof(champ));
        for (int i = 0; i < temp.size(); i++){
            champ[i] = temp[i];
        }
        strncpy(pick_4_red_team, champ, sizeof(pick_4_red_team) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(champ, 0, sizeof(champ));
        for (int i = 0; i < temp.size(); i++){
            champ[i] = temp[i];
        }
        strncpy(pick_5_red_team, champ, sizeof(pick_5_red_team) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        char player[15] = "";
        for (int i = 0; i < temp.size(); i++){
            player[i] = temp[i];
        }
        strncpy(top_blue_team, player, sizeof(top_blue_team) - 1);
        
        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(player, 0, sizeof(player));
        for (int i = 0; i < temp.size(); i++){
            player[i] = temp[i];
        }
        strncpy(jungler_blue_team, player, sizeof(jungler_blue_team) - 1);
        
        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(player, 0, sizeof(player));
        for (int i = 0; i < temp.size(); i++){
            player[i] = temp[i];
        }
        strncpy(mid_blue_team, player, sizeof(mid_blue_team) - 1);
        
        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(player, 0, sizeof(player));
        for (int i = 0; i < temp.size(); i++){
            player[i] = temp[i];
        }
        strncpy(adc_blue_team, player, sizeof(adc_blue_team) - 1);
        
        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(player, 0, sizeof(player));
        for (int i = 0; i < temp.size(); i++){
            player[i] = temp[i];
        }
        strncpy(support_blue_team, player, sizeof(support_blue_team) - 1);
        
        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(player, 0, sizeof(player));
        for (int i = 0; i < temp.size(); i++){
            player[i] = temp[i];
        }
        strncpy(top_red_team, player, sizeof(top_red_team) - 1);
        
        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(player, 0, sizeof(player));
        for (int i = 0; i < temp.size(); i++){
            player[i] = temp[i];
        }
        strncpy(jungler_red_team, player, sizeof(jungler_red_team) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(player, 0, sizeof(player));
        for (int i = 0; i < temp.size(); i++){
            player[i] = temp[i];
        }
        strncpy(mid_red_team, player, sizeof(mid_red_team) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(player, 0, sizeof(player));
        for (int i = 0; i < temp.size(); i++){
            player[i] = temp[i];
        }
        strncpy(adc_red_team, player, sizeof(adc_red_team) - 1);

        temp = data.substr(0, data.find(","));
        data = data.substr(data.find(",") + 1);
        memset(player, 0, sizeof(player));
        for (int i = 0; i < temp.size(); i++){
            player[i] = temp[i];
        }
        strncpy(support_red_team, player, sizeof(support_red_team) - 1);
    }

    variant<int, float, string>getKey() const {
        switch (key) {
            case 0:
                return season;
            case 1:
                return date;
            case 2:
                return event;
            case 3:
                return patch;
            case 4:
                return blue_team;
            case 5:
                return red_team;
            case 6:
                return winner;
            case 7:
                return ban_1_blue_team;
            case 8:
                return ban_2_blue_team;
            case 9:
                return ban_3_blue_team;
            case 10:
                return ban_4_blue_team;
            case 11:
                return ban_5_blue_team;
            case 12:
                return ban_1_red_team;
            case 13:
                return ban_2_red_team;
            case 14:
                return ban_3_red_team;
            case 15:
                return ban_4_red_team;
            case 16:
                return ban_5_red_team;
            case 17:
                return pick_1_blue_team;
            case 18:
                return pick_2_blue_team;
            case 19:
                return pick_3_blue_team;
            case 20:
                return pick_4_blue_team;
            case 21:
                return pick_5_blue_team;
            case 22:
                return pick_1_red_team;
            case 23:
                return pick_2_red_team;
            case 24:
                return pick_3_red_team;
            case 25:
                return pick_4_red_team;
            case 26:
                return pick_5_red_team;
            case 27:
                return top_blue_team;
            case 28:
                return jungler_blue_team;
            case 29:
                return mid_blue_team;
            case 30:
                return adc_blue_team;
            case 31:
                return support_blue_team;
            case 32:
                return top_red_team;
            case 33:
                return jungler_red_team;
            case 34:
                return mid_red_team;
            case 35:
                return adc_red_team;
            case 36:
                return support_red_team;
            default:
                return -1;
        }
    }

    void print(){
        cout << "Season: " << season << endl;
        cout << "Date: " << date << endl;
        cout << "Event: " << event << endl;
        cout << "Patch: " << patch << endl;
        cout << "Blue Team: " << blue_team << endl;
        cout << "Red Team: " << red_team << endl;
        cout << "Winner: " << winner << endl;
        cout << "Ban 1 Blue Team: " << ban_1_blue_team << endl;
        cout << "Ban 2 Blue Team: " << ban_2_blue_team << endl;
        cout << "Ban 3 Blue Team: " << ban_3_blue_team << endl;
        cout << "Ban 4 Blue Team: " << ban_4_blue_team << endl;
        cout << "Ban 5 Blue Team: " << ban_5_blue_team << endl;
        cout << "Ban 1 Red Team: " << ban_1_red_team << endl;
        cout << "Ban 2 Red Team: " << ban_2_red_team << endl;
        cout << "Ban 3 Red Team: " << ban_3_red_team << endl;
        cout << "Ban 4 Red Team: " << ban_4_red_team << endl;
        cout << "Ban 5 Red Team: " << ban_5_red_team << endl;
        cout << "Pick 1 Blue Team: " << pick_1_blue_team << endl;
        cout << "Pick 2 Blue Team: " << pick_2_blue_team << endl;
        cout << "Pick 3 Blue Team: " << pick_3_blue_team << endl;
        cout << "Pick 4 Blue Team: " << pick_4_blue_team << endl;
        cout << "Pick 5 Blue Team: " << pick_5_blue_team << endl;
        cout << "Pick 1 Red Team: " << pick_1_red_team << endl;
        cout << "Pick 2 Red Team: " << pick_2_red_team << endl;
        cout << "Pick 3 Red Team: " << pick_3_red_team << endl;
        cout << "Pick 4 Red Team: " << pick_4_red_team << endl;
        cout << "Pick 5 Red Team: " << pick_5_red_team << endl;
        cout << "Top Blue Team: " << top_blue_team << endl;
        cout << "Jungler Blue Team: " << jungler_blue_team << endl;
        cout << "Mid Blue Team: " << mid_blue_team << endl;
        cout << "ADC Blue Team: " << adc_blue_team << endl;
        cout << "Support Blue Team: " << support_blue_team << endl;
        cout << "Top Red Team: " << top_red_team << endl;
        cout << "Jungler Red Team: " << jungler_red_team << endl;
        cout << "Mid Red Team: " << mid_red_team << endl;
        cout << "ADC Red Team: " << adc_red_team << endl;
        cout << "Support Red Team: " << support_red_team << endl;
    }

    bool operator==(const MatchStats &other) const {
        return key == other.key && season == other.season && strcmp(date, other.date) == 0 && strcmp(event, other.event) == 0 && patch == other.patch && strcmp(blue_team, other.blue_team) == 0 && strcmp(red_team, other.red_team) == 0 && strcmp(winner, other.winner) == 0 && strcmp(ban_1_blue_team, other.ban_1_blue_team) == 0 && strcmp(ban_2_blue_team, other.ban_2_blue_team) == 0 && strcmp(ban_3_blue_team, other.ban_3_blue_team) == 0 && strcmp(ban_4_blue_team, other.ban_4_blue_team) == 0 && strcmp(ban_5_blue_team, other.ban_5_blue_team) == 0 && strcmp(ban_1_red_team, other.ban_1_red_team) == 0 && strcmp(ban_2_red_team, other.ban_2_red_team) == 0 && strcmp(ban_3_red_team, other.ban_3_red_team) == 0 && strcmp(ban_4_red_team, other.ban_4_red_team) == 0 && strcmp(ban_5_red_team, other.ban_5_red_team) == 0 && strcmp(pick_1_blue_team, other.pick_1_blue_team) == 0 && strcmp(pick_2_blue_team, other.pick_2_blue_team) == 0 && strcmp(pick_3_blue_team, other.pick_3_blue_team) == 0 && strcmp(pick_4_blue_team, other.pick_4_blue_team) == 0 && strcmp(pick_5_blue_team, other.pick_5_blue_team) == 0 && strcmp(pick_1_red_team, other.pick_1_red_team) == 0 && strcmp(pick_2_red_team, other.pick_2_red_team) == 0 && strcmp(pick_3_red_team, other.pick_3_red_team) == 0 && strcmp(pick_4_red_team, other.pick_4_red_team) == 0 && strcmp(pick_5_red_team, other.pick_5_red_team) == 0 && strcmp(top_blue_team, other.top_blue_team) == 0 && strcmp(jungler_blue_team, other.jungler_blue_team) == 0 && strcmp(mid_blue_team, other.mid_blue_team) == 0 && strcmp(adc_blue_team, other.adc_blue_team) == 0 && strcmp(support_blue_team, other.support_blue_team) == 0 && strcmp(top_red_team, other.top_red_team) == 0 && strcmp(jungler_red_team, other.jungler_red_team) == 0 && strcmp(mid_red_team, other.mid_red_team) == 0 && strcmp(adc_red_team, other.adc_red_team) == 0 && strcmp(support_red_team, other.support_red_team) == 0;
    }

    void setKey(variant<int, float, string> k){
        if (key == 0) season = get<int>(k);
        else if (key == 1) strcpy(date, get<string>(k).c_str());
        else if (key == 2) strcpy(event, get<string>(k).c_str());
        else if (key == 3) patch = get<float>(k);
        else if (key == 4) strcpy(blue_team, get<string>(k).c_str());
        else if (key == 5) strcpy(red_team, get<string>(k).c_str());
        else if (key == 6) strcpy(winner, get<string>(k).c_str());
        else if (key == 7) strcpy(ban_1_blue_team, get<string>(k).c_str());
        else if (key == 8) strcpy(ban_2_blue_team, get<string>(k).c_str());
        else if (key == 9) strcpy(ban_3_blue_team, get<string>(k).c_str());
        else if (key == 10) strcpy(ban_4_blue_team, get<string>(k).c_str());
        else if (key == 11) strcpy(ban_5_blue_team, get<string>(k).c_str());
        else if (key == 12) strcpy(ban_1_red_team, get<string>(k).c_str());
        else if (key == 13) strcpy(ban_2_red_team, get<string>(k).c_str());
        else if (key == 14) strcpy(ban_3_red_team, get<string>(k).c_str());
        else if (key == 15) strcpy(ban_4_red_team, get<string>(k).c_str());
        else if (key == 16) strcpy(ban_5_red_team, get<string>(k).c_str());
        else if (key == 17) strcpy(pick_1_blue_team, get<string>(k).c_str());
        else if (key == 18) strcpy(pick_2_blue_team, get<string>(k).c_str());
        else if (key == 19) strcpy(pick_3_blue_team, get<string>(k).c_str());
        else if (key == 20) strcpy(pick_4_blue_team, get<string>(k).c_str());
        else if (key == 21) strcpy(pick_5_blue_team, get<string>(k).c_str());
        else if (key == 22) strcpy(pick_1_red_team, get<string>(k).c_str());
        else if (key == 23) strcpy(pick_2_red_team, get<string>(k).c_str());
        else if (key == 24) strcpy(pick_3_red_team, get<string>(k).c_str());
        else if (key == 25) strcpy(pick_4_red_team, get<string>(k).c_str());
        else if (key == 26) strcpy(pick_5_red_team, get<string>(k).c_str());
        else if (key == 27) strcpy(top_blue_team, get<string>(k).c_str());
        else if (key == 28) strcpy(jungler_blue_team, get<string>(k).c_str());
        else if (key == 29) strcpy(mid_blue_team, get<string>(k).c_str());
        else if (key == 30) strcpy(adc_blue_team, get<string>(k).c_str());
        else if (key == 31) strcpy(support_blue_team, get<string>(k).c_str());
        else if (key == 32) strcpy(top_red_team, get<string>(k).c_str());
        else if (key == 33) strcpy(jungler_red_team, get<string>(k).c_str());
        else if (key == 34) strcpy(mid_red_team, get<string>(k).c_str());
        else if (key == 35) strcpy(adc_red_team, get<string>(k).c_str());
        else if (key == 36) strcpy(support_red_team, get<string>(k).c_str());
    }
};