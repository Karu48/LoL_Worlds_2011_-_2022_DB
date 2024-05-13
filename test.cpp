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

    data = "8,Main,Phong_V_c5-_a9-_Buffalo,BigKoro,6,2,4,33.3,3.33,2.67,3.0,2.38,346.67,9.85,15.1,430,,,67.9,35.7,24.4";
    PlayerStats player(data, "player");
    player.print();
    visit([](auto x){cout << x << endl;}, player.getKey());

    return 0;
}