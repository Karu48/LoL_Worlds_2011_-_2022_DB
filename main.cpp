#include "parser/parser.hh"

int main(){
    TableFile tables("tables.dat");
    string input;
    while (input != "exit"){
        getline(cin, input);
        Scanner scanner(input.c_str());
        solve(scanner, tables);
    }
}