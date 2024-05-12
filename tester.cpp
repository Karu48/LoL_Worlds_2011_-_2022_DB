#include "championStats.hpp"
#include "matchStats.hpp"
#include "playerStats.hpp"

int main(){
    cout << "Testing ChampionStats struct:\n";
    string data = "1,Main,Nidalee,19,67.9,15.0,4,3.0,3,1,75.0,2.5,2.0,3.5,3.0,192.25,6.03,9.7,304.0,,,,,";
    ChampionStats champ(data);
    champ.print();

    cout << "\n\n Testing MatchStats struct:\n";
    string data2 = "1,2011-06-20,Main,,Against_All_authority,Fnatic,Fnatic,Alistar,Ashe,Vladimir,,,Rumble,Nunu,Amumu,,,Nidalee,Warwick,Anivia,Miss Fortune,Sona,Gragas,Jarvan IV,Malzahar,Corki,Janna,sOAZ,Linak,MoMa,YellOwStaR,Kujaa,Shushei,Cyanide,xPeke,Lamia,Mellisan";
    MatchStats match(data2);
    match.print();

    cout << "\n\n Testing PlayerStats struct:\n";
    string data3 = "1,Main,Counter_Logic_Gaming,Chauster,6,3,3,50.0,3.17,1.67,2.5,3.4,221.0,6.21,10.4,293,,,,,";
    PlayerStats player(data3);
    player.print();

    return 0;
}
