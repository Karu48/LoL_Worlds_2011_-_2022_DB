#include "struct/championStats.hpp"
#include "struct/matchStats.hpp"
#include "struct/playerStats.hpp"

int main(){
    string data = "7,Main,Fizz,4,5.0,,4,2.0,3,1,75.0,2.5,1.25,4.0,5.2,275.25,7.86,13.2,375.0,,,76.5,29.4,20.6";
    ChampionStats champ(data, "wins");
    champ.print();
    visit([](auto x){cout << x << endl;}, champ.getKey());

    cout << "\n-------------------------------------------------------------\n";

    data = "12,2022-10-03,Play in,12.18,LOUD,DetonatioN_FocusMe,LOUD,Trundle,Kai'Sa,Yuumi,Ezreal,Leona,Sylas,Aatrox,Kalista,Lissandra,Zoe,Olaf,Maokai,Akali,Miss Fortune,Amumu,Gnar,Sejuani,Azir,Caitlyn,Morgana,Robo,Croc,tinowns,Brance,Ceos,Evi,Steal,Yaharong,Yutapon,Harp";
    MatchStats match(data, "season");
    match.print();
    visit([](auto x){cout << x << endl;}, match.getKey());

    cout << "\n-------------------------------------------------------------\n";

    data = "11,Main,T1,Keria,14,10,4,71.4,0.57,1.21,8.57,7.53,27.07,0.87,7.7,248,3800.0,123.0,78.0,4.9,13.5";
    PlayerStats player(data, "player");
    player.print();
    visit([](auto x){cout << x << endl;}, player.getKey());

    return 0;
}