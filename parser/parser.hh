#ifndef IMP_PARSER
#define IMP_PARSER

#include "table.hpp"

class Token {
public:
  enum Type { ERR, END, SELECT, FROM, INSERT, VALUES, DELETE, STRING, IF, CREATE, TABLE, FILE, USING, STRUCT, INT, FLOAT, EQUAL, GREATER, LESSER, GREATEREQUAL, LESSEREQUAL, NOTEQUAL, AND, OR, WHERE, ALL, INTO };
  static const char* token_names[28];
  Type type;
  string lexema;
  Token(Type);
  Token(Type, const string source);
};


class Scanner {
public:
  Scanner(const char* in_s);
  Token* nextToken();
  ~Scanner();  
private:
  string input;
  int first, current;
  unordered_map<string, Token::Type> reserved;
  char nextChar();
  void rollBack();
  void startLexema();
  string getLexema();
  Token::Type checkReserved(string);
};

const char* Token::token_names[28] = { "ERR", "END", "SELECT", "FROM", "INSERT", "VALUES", "DELETE", "STRING", "IF", "CREATE", "TABLE", "FILE", "USING", "STRUCT", "INT", "FLOAT", "EQUAL", "GREATER", "LESSER", "GREATER EQUAL", "LESSER EQUAL", "NOT EQUAL", "AND", "OR", "WHERE", "ALL", "INTO" };

Token::Token(Type type):type(type) { lexema = ""; }

Token::Token(Type type, const string source):type(type) {
  lexema = source;
}

std::ostream& operator << ( std::ostream& outs, const Token & tok )
{
  if (tok.lexema.empty())
    return outs << Token::token_names[tok.type];
  else
    return outs << Token::token_names[tok.type] << "(" << tok.lexema << ")";
}

std::ostream& operator << ( std::ostream& outs, const Token* tok ) {
  return outs << *tok;
}

Scanner::Scanner(const char* s):input(s),first(0), current(0) {
      reserved["if"] = Token::IF;
      reserved["select"] = Token::SELECT;
      reserved["from"] = Token::FROM;
      reserved["insert"] = Token::INSERT;
      reserved["values"] = Token::VALUES;
      reserved["delete"] = Token::DELETE;
      reserved["create"] = Token::CREATE;
      reserved["table"] = Token::TABLE;
      reserved["file"] = Token::FILE;
      reserved["using"] = Token::USING;
      reserved["AVL"] = Token::STRUCT;
      reserved["hash"] = Token::STRUCT;
      reserved["ISAM"] = Token::STRUCT; 
      reserved["and"] = Token::AND;
      reserved["or"] = Token::OR;
      reserved["where"] = Token::WHERE;
    }

Token* Scanner::nextToken() {
  Token* token;
  char c;
  // consume whitespaces
  c = nextChar();
  while (c == ' ') c = nextChar();
  if (c == '\0') return new Token(Token::END);
  startLexema();
  if (isdigit(c)) {
    c = nextChar();
    while (isdigit(c)) c = nextChar();
    if (c == '.') {
      c = nextChar();
      while (isdigit(c)) c = nextChar();
      rollBack();
      token = new Token(Token::FLOAT, getLexema());
    } else {
      rollBack();
      token = new Token(Token::INT, getLexema());
    }
    
  } else if (isalpha(c)) {
    c = nextChar();
    while (isalpha(c) || isdigit(c) || c=='_') c = nextChar();
    rollBack();
    string lex = getLexema();
    Token::Type ttype = checkReserved(lex);
    if (ttype != Token::ERR)
      token = new Token(ttype);
    else
      token = new Token(Token::STRING, getLexema()); 
  } else if (strchr("!<>=*", c)) {
    switch(c) {
    case '=': token = new Token(Token::EQUAL); break;
    case '!': c = nextChar(); 
      if (c == '=') token = new Token(Token::NOTEQUAL);
      else token = new Token(Token::ERR, getLexema());
      break;
    case '>': c = nextChar();
      if (c == '=') token = new Token(Token::GREATEREQUAL);
      else token = new Token(Token::GREATER);
      break;
    case '<': c = nextChar();
      if (c == '=') token = new Token(Token::LESSEREQUAL);
      else token = new Token(Token::LESSER);
      break;
    case '*' : token = new Token(Token::ALL, getLexema()); break;
    default: cout << "No deberia llegar aca" << endl;
    }
  } else {
    token = new Token(Token::ERR, getLexema());
  }
  return token;
}

Scanner::~Scanner() { }

char Scanner::nextChar() {
  int c = input[current];
  current++;
  return c;
}

void Scanner::rollBack() { // retract
  current--;
}

void Scanner::startLexema() {
  first = current-1;
  return;
}

string Scanner::getLexema() {
  return input.substr(first,current-first);
}

Token::Type Scanner::checkReserved(string lexema) {
  std::unordered_map<std::string,Token::Type>::const_iterator it = reserved.find (lexema);
  if (it == reserved.end())
    return Token::ERR;
  else
    return it->second;
}

void solve(Scanner scanner){
  Token* token;
  do {
    token = scanner.nextToken();
    
    if (token->type == Token::CREATE) {
      token = scanner.nextToken();
      if (token->type != Token::TABLE) return;
      token = scanner.nextToken();
      if (token->type != Token::STRING) return;
      string name = token->lexema;
      token = scanner.nextToken();
      if (token->type != Token::FROM) return;
      token = scanner.nextToken();
      if (token->type != Token::FILE) return;
      token = scanner.nextToken();
      if (token->type != Token::STRING) return;
      string file = token->lexema;
      token = scanner.nextToken();
      if (token->type != Token::USING) return;
      token = scanner.nextToken();
      if (token->type != Token::STRUCT) return;
      token = scanner.nextToken();
      if (token->type != Token::STRING) return;
      string structure = token->lexema;
      cout << "CREATE TABLE " << name << " FROM " << file << " USING " << structure << endl;
    }

    if (token->type == Token::INSERT) {
      token = scanner.nextToken();
      if (token->type != Token::INTO) return;
      token = scanner.nextToken();
      if (token->type != Token::STRING) return;
      string name = token->lexema;
      token = scanner.nextToken();
      if (token->type != Token::VALUES) return;
      token = scanner.nextToken();
      if (token->type != Token::STRING) return;
      string values = token->lexema;
      cout << "INSERT INTO " << name << " VALUES " << values << endl;
    }

    

  } while (token->type != Token::END);
}

#endif
