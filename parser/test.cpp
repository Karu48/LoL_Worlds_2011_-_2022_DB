#include "parser.hh"

using namespace std;

int main(){
    TableFile tables("tables.dat");
    string input;
    getline(cin, input);
    Scanner scanner(input.c_str());
    Token* token;
    do {
        token = scanner.nextToken();
        cout << token->token_names[token->type] << "(" << token->lexema << ")" << endl;
    } while (token->type != Token::END);
    Scanner scanner2(input.c_str());
    solve(scanner2, tables);
    return 0;
}