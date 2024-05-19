#include "parser/parser.hh"

int main(){
    TableFile tables("tables.dat");
    string input;
    while (input != "exit"){
        getline(cin, input);
        Scanner a(input.c_str());
        Token* token;
        do {
            token = a.nextToken();
            cout << token->token_names[token->type] << "(" << token->lexema << ")" << endl;
        } while (token->type != Token::END);
        Scanner scanner(input.c_str());
        solve(scanner, tables);
    }
}