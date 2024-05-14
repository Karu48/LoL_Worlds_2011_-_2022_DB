#include "parser.hh"


const char* Token::token_names[27] = { "ERR", "END", "SELECT", "FROM", "INSERT", "VALUES", "DELETE", "STRING", "IF", "CREATE", "TABLE", "FILE", "USING", "STRUCT", "INT", "FLOAT", "EQUAL", "GREATER", "LESSER", "GREATER EQUAL", "LESSER EQUAL", "NOT EQUAL", "AND", "OR", "WHERE", "ALL" };

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



/* ***************** Parser ********************* */

/*

// match and consume next token
bool Parser::match(Token::Type ttype) {
  if (check(ttype)) {
    advance();
    return true;
  }
  return false;
}

bool Parser::check(Token::Type ttype) {
  if (isAtEnd()) return false;
  return current->type == ttype;
}


bool Parser::advance() {
  if (!isAtEnd()) {
    Token* temp =current;
    if (previous) delete previous;
    current = scanner->nextToken();
    previous = temp;
    if (check(Token::ERR)) {
      cout << "Parse error, unrecognised character: " << current->lexema << endl;
      exit(0);
    }
    return true;
  }
  return false;
} 

bool Parser::isAtEnd() {
  return (current->type == Token::END);
} 

Parser::Parser(Scanner* sc):scanner(sc) {
  previous = current = NULL;
  return;
};

Program* Parser::parse() {
  current = scanner->nextToken();
  if (check(Token::ERR)) {
      cout << "Error en scanner - caracter invalido" << endl;
      exit(0);
  }
  Program* p = parseProgram();
  if (current->type != Token::END) {
    cout << "Esperaba fin-de-input, se encontro " << current << endl;
    delete p;
    p = NULL;
  }

  if (current) delete current;
  return p;
}

Program* Parser::parseProgram() {
  Program* p = new Program();
  // parse statement list
  p->add(parseStatement());
  while(match(Token::SEMICOLON) || match(Token::SALTO)) {
    p->add(parseStatement());
  }
  return p;
}

Stm* Parser::parseStatement() {
  Stm* s = NULL;
  Exp* e;
  if (match(Token::ID)) {
    string lex = previous->lexema;
    if (!match(Token::ASSIGN)) {
      cout << "Error: esperaba =" << endl;
      exit(0);
    }
    s = new AssignStatement(lex, parseExpression());
    //memoria_update(lex, v);
  } else if (match(Token::PRINT)) {
    if (!match(Token::LPAREN)) {
      cout << "Error: esperaba ( " << endl;
      exit(0);
    }
    e = parseExpression();
    if (!match(Token::RPAREN)) {
      cout << "Error: esperaba )" << endl;
      exit(0);
    }
    s = new PrintStatement(e);
  } else {
    cout << "No se encontro Statement" << endl;
    exit(0);
  }
  return s;
}


Exp* Parser::parseExpression() {
  Exp *e, *rhs;
  e = parseTerm();
  while(match(Token::MINUS) || match(Token::PLUS)) {
    Token::Type op = previous->type;
    BinaryOp binop = (op==Token::MINUS)? MINUS : PLUS;
    rhs = parseTerm();
    e = new BinaryExp(e, rhs, binop);
  }
  return e;
}

Exp* Parser::parseTerm() {
  Exp *e, *rhs;
  e = parseFExp();
  while(match(Token::MULT) || match(Token::DIV)) {
    Token::Type op = previous->type;
    BinaryOp binop = (op==Token::MULT)?MULT : DIV;
    rhs = parseFExp();
    e = new BinaryExp(e, rhs, binop);
  }
  return e;
}

Exp* Parser::parseFExp() {
  Exp *lhs, *rhs;
  lhs = parseFactor();
  if (match(Token::EXP)) {
    return new BinaryExp(lhs, parseFExp(), EXP);
  }
  return lhs; 
}

Exp* Parser::parseFactor() {
  if (match(Token::NUM)) {
    return new NumberExp(stoi(previous->lexema));
  }
  if (match(Token::ID)) {
    return new IdExp(previous->lexema);
  }
  if (match(Token::LPAREN)) {
    Exp* e = parseExpression();
    if (!match(Token::RPAREN)) {
      cout << "Expecting right parenthesis" << endl;
      exit(0);
    }
    // return e; is fine too
    return new ParenthExp(e);
  }

  if (match(Token::LOG)){
    if (!match(Token::LPAREN)) {
      cout << "Expecting left parenthesis" << endl;
      exit(0);
    }
    Exp* e = parseExpression();
    if (!match(Token::RPAREN)) {
      cout << "Expecting right parenthesis" << endl;
      exit(0);
    }
    return new LogExp(e);
  }

  if (match(Token::SQRT)){
    if (!match(Token::LPAREN)) {
      cout << "Expecting left parenthesis" << endl;
      exit(0);
    }
    Exp* e = parseExpression();
    if (!match(Token::RPAREN)) {
      cout << "Expecting right parenthesis" << endl;
      exit(0);
    }
    return new SqrtExp(e);
  }
  cout << "Couldn't find match for token: " << current << endl;
  exit(0);
}


*/






// ---------------------------------------------------



