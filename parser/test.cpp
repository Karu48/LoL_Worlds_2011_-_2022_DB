#include "parser.hh"

using namespace std;

int main(){
    string input;
    getline(cin, input);
    Scanner scanner(input.c_str());
    Token* token;
    do {
        token = scanner.nextToken();
        cout << token->token_names[token->type] << "(" << token->lexema << ")" << endl;
    } while (token->type != Token::END);
    return 0;
}