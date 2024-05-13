#include "parser.hh"

using namespace std;

int main(){
    string input = "select xd from table holi delete from tablita where xd = 1.0 and xd = 2.0";
    Scanner scanner(input.c_str());
    Token* token;
    do {
        token = scanner.nextToken();
        cout << token->token_names[token->type] << "(" << token->lexema << ")" << endl;
    } while (token->type != Token::END);
    return 0;
}