#ifndef IMP_PARSER
#define IMP_PARSER

#include "table.hpp"

class Token {
public:
  enum Type { ERR, END, SELECT, FROM, INSERT, VALUES, DELETE, STRING, IF, CREATE, TABLE, FILE, USING, STRUCT, INT, FLOAT, EQUAL, GREATER, LESSER, GREATEREQUAL, LESSEREQUAL, NOTEQUAL, AND, OR, WHERE, ALL, INTO, INDEX, SEQUENTIAL, HASH, ISAM, CHAMPION, MATCH, PLAYER, KEY, BETWEEN };
  static const char* token_names[37];
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

const char* Token::token_names[37] = { "ERR", "END", "SELECT", "FROM", "INSERT", "VALUES", "DELETE", "STRING", "IF", "CREATE", "TABLE", "FILE", "USING", "STRUCT", "INT", "FLOAT", "EQUAL", "GREATER", "LESSER", "GREATER EQUAL", "LESSER EQUAL", "NOT EQUAL", "AND", "OR", "WHERE", "ALL", "INTO", "INDEX", "SEQUENTIAL", "HASH", "ISAM", "CHAMPION", "MATCH", "PLAYER", "KEY", "BETWEEN"};

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
      reserved["sequential"] = Token::SEQUENTIAL;
      reserved["hash"] = Token::HASH;
      reserved["ISAM"] = Token::ISAM; 
      reserved["and"] = Token::AND;
      reserved["or"] = Token::OR;
      reserved["where"] = Token::WHERE;
      reserved["champion"] = Token::CHAMPION;
      reserved["match"] = Token::MATCH;
      reserved["player"] = Token::PLAYER;
      reserved["index"] = Token::INDEX;
      reserved["struct"] = Token::STRUCT;
      reserved["key"] = Token::KEY; 
      reserved["into"] = Token::INTO;
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
    
  } else if (isalpha(c) || c == '_' || c == ',' || c == '.' || c == '/') { 
    c = nextChar();
    while (isalpha(c) || isdigit(c) || c=='_' || c==',' || c=='.' || c == '/') c = nextChar();
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


void create(string name, string file, string structure, string index, string key, TableFile tables){
  Table t(name, structure, key);
  tables.insert(t);
  if (index == "sequential") {
    SequentialFile filex(name + ".dat");
    fstream f(file, ios::in);
    string line;
    getline(f, line);
    while (getline(f, line)) {
      Register r(line, key, structure);
      filex.insert(r);
    }
  } else if (index == "hash") {
    ExtendibleHashing<Register> filex(name + ".dat");
    fstream f(file, ios::in);
    string line;
    getline(f, line);
    while (getline(f, line)) {
      Register r(line, key, structure);
      filex.insert(r);
    }
  } else if (index == "ISAM") {
    ISAM filex(name + ".dat");
    filex.loadCSV(file);
  }
  cout << "Tabla creada" << endl;
}

void insert(string table, string values, TableFile tables){
  Table t = tables.get(table);
  if (t.type == "sequential") {
    SequentialFile file(t.name + ".dat");
    Register r(values, t.key, t.type);
    file.insert(r);
  } else if (t.type == "hash") {
    ExtendibleHashing<Register> file(t.name + ".dat");
    Register r(values, t.key, t.type);
    file.insert(r);
  } else if (t.type == "ISAM") {
    ISAM file(t.name + ".dat");
    Record r(values, t.key, t.type);
    file.insert(r);
  }
  cout << "Registro insertado" << endl;
}

void select(string values, string table, TableFile tables){
  Table t = tables.get(table);
  if (t.type == "sequential") {
    SequentialFile file(t.name + ".dat");
    vector<Register> records = file.getRegisters();
    for (auto r : records) {
      visit([](auto&& arg) { arg.print(); }, r.data);
    }
  } else if (t.type == "hash") {
    cout << "Hash no tiene esta funcion" << endl;
  } else if (t.type == "ISAM") {
    ISAM file(t.name + ".dat");
    file.printAll();
  }
}

void select(string values, string table, string condition, string op, variant<int, float, string> value, TableFile tables){
  Table t = tables.get(table);
  if (t.type == "sequential") {
    SequentialFile file(t.name + ".dat");
    if (condition == "EQUAL"){
      vector<Register> regs = file.searchRange(value, value);
      for (auto r : regs) {
        visit([](auto&& arg) { arg.print(); }, r.data);
      }
    }
  } else if (t.type == "hash") {
    ExtendibleHashing<Register> file(t.name + ".dat");
    file.searchByKey(value, t.key, t.type);
  } else if (t.type == "ISAM") {
    ISAM file(t.name + ".dat");
    int key = get<int>(value);
    // ISAM solo funciona para enteros
    file.search(key);
  }
}

void remove(string table, string condition, string op, variant<int, float, string> value, TableFile tables){
  Table t = tables.get(table);
  if (t.type == "sequential") {
    SequentialFile file(t.name + ".dat");
    if (condition == "EQUAL"){
      file.remove(value);
    }
  } else if (t.type == "hash") {
    ExtendibleHashing<Register> file(t.name + ".dat");
    cout << "Hash no tiene esta funcion" << endl;
  } else if (t.type == "ISAM") {
    ISAM file(t.name + ".dat");
    int key = get<int>(value);
    // ISAM solo funciona para enteros
    file.remove(key);
  }
  cout << "Registro eliminado" << endl;
}

void solve(Scanner scanner, TableFile tables){
  Token* token;

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
    if (token->type != Token::CHAMPION && token->type != Token::MATCH && token->type != Token::PLAYER) return;
    string structure = token->token_names[token->type];
    token = scanner.nextToken();
    if (token->type != Token::INDEX) return;
    token = scanner.nextToken();
    if (token->type != Token::SEQUENTIAL && token->type != Token::HASH && token->type != Token::ISAM ) return;
    string index = token->token_names[token->type];
    token = scanner.nextToken();
    if (token->type != Token::KEY) return;
    token = scanner.nextToken();
    if (token->type != Token::STRING) return;
    string key = token->lexema;
    cout << name << " " << file << " " << structure << " " << index << " " << key << endl;
    create(name, file, structure, index, key, tables);
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
    insert(name, values, tables);
  }

  if (token->type == Token::SELECT) {
    token = scanner.nextToken();
    if (token->type != Token::ALL && token->type != Token::STRING) return;
    string values;
    if (token->type == Token::STRING) values = token->lexema;
    else values = "*";

    token = scanner.nextToken();
    if (token->type != Token::FROM) return;
    token = scanner.nextToken();
    if (token->type != Token::STRING) return;
    string table = token->lexema;
    token = scanner.nextToken();
    if (token->type != Token::WHERE && token->type != Token::END) return;
    if (token->type == Token::END) {
      select(values, table, tables);
      return;
    }
    token = scanner.nextToken();
    if (token->type != Token::STRING) return;
    string condition = token->lexema;
    token = scanner.nextToken();
    if (token->type != Token::BETWEEN) cout << "Error" << endl;
    if (token->type != Token::EQUAL) return;
    string op = token->token_names[token->type];
    token = scanner.nextToken();
    if (token->type != Token::STRING && token->type != Token::INT && token->type != Token::FLOAT) return;
    variant<int, float, string> value;
    if (token->type == Token::INT) value = stoi(token->lexema);
    else if (token->type == Token::FLOAT) value = stof(token->lexema);
    else value = token->lexema;
    select(values, table, condition, op, value, tables);
  }

  if (token->type == Token::DELETE) {
    token = scanner.nextToken();
    if (token->type != Token::FROM) return;
    token = scanner.nextToken();
    if (token->type != Token::STRING) return;
    string table = token->lexema;
    token = scanner.nextToken();
    if (token->type != Token::WHERE) return;
    token = scanner.nextToken();
    if (token->type != Token::STRING) return;
    string condition = token->lexema;
    token = scanner.nextToken();
    if (token->type != Token::BETWEEN) cout << "Error" << endl;
    if (token->type != Token::EQUAL) return;
    string op = token->token_names[token->type];
    token = scanner.nextToken();
    if (token->type != Token::STRING && token->type != Token::INT && token->type != Token::FLOAT) return;
    variant<int, float, string> value;
    if (token->type == Token::INT) value = stoi(token->lexema);
    else if (token->type == Token::FLOAT) value = stof(token->lexema);
    else value = token->lexema;
    remove(table, condition, op, value, tables);
  }
}

#endif
