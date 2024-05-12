#include <iostream>
#include <cstring>

using namespace std;

struct MatchStats{
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

    MatchStats(string data){
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
};