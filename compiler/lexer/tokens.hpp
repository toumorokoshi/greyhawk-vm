#include <string>
#include <vector>

#ifndef LEXER_TOKEN_HPP
#define LEXER_TOKEN_HPP

namespace lexer {

  // NOTE: all tokens should be initialized as const
  // Tokens are (should be) immutable and should be treated as such

  class Token {
  private:
    std::string name;
  public:
    Token() : name("nothing") {}
    Token(std::string _name) : name(_name) {}
    virtual ~Token() {}
    virtual std::string getDescription() const { return "token: " + name; }
    // returns true if it's a terminal token (this is for the parser)
    virtual bool isTerminal() { return true; }
  };

  class Operator :  public Token {
    typedef std::pair<std::string, const Token*> OperatorPair;
  public:
    const std::string symbols;
    const int operatorCode;
    Operator(std::string _symbols, int operatorCode) :
      symbols(_symbols),
      operatorCode(operatorCode) {};
    std::string getDescription() const { return symbols; }
    OperatorPair getOperatorPair () const { return OperatorPair(symbols, this); }
  };

  class Keyword : public Token {
  public:
    const std::string symbol;
    Keyword(std::string _symbol) : symbol(_symbol) {}
    std::string getDescription() const { return "keyword: " + symbol; }
  };

  class Integer : public Token {
  public:
    const int value;
    Integer(int _value): value(_value) {}
    std::string getDescription() const { return "integer: " + std::to_string(value); }
  };

  class Double : public Token {
  public:
    const double value;
    Double(double _value): value(_value) {}
    std::string getDescription() const { return "double: " + std::to_string(value); }
  };

  class String: public Token {
  public:
    const std::string value;
    String(std::string _value) : value(_value) {}
    std::string getDescription() const { return "string: \"" + value + "\""; }
  };

  class Identifier : public Token {
  public:
    const std::string name;
    Identifier(std::string _name) : name(_name) {}
    std::string getDescription() const { return "identifier: " + name; }
  };

  typedef std::vector<const Token*> TokenVector;
  typedef std::vector<const Keyword*> KeywordVector;

  typedef std::pair<std::string, const Token*> OperatorPair;
  typedef std::vector<OperatorPair> OperatorPairVector;

  TokenVector tokenize(std::string input);

  // the actual tokens
  extern const Token T_INDENT;
  extern const Token T_UNINDENT;
  extern const Token T_LPAREN;
  extern const Token T_RPAREN;

  // keywords
  extern const Keyword T_ELSE;
  extern const Keyword T_IF;
  extern const Keyword T_RETURN;

  // constants
  extern const Keyword T_TRUE;
  extern const Keyword T_FALSE;


  enum OPERATOR_CODES {
    COMMA,
    DOT,
    PLUS,
    MINUS,
    MUL,
    DIV,
    DECLARE,
    ASSIGN,
    COMPARE_EQUAL,
    COMPARE_NOT_EQUAL,
    COMPARE_LEQ,
    COMPARE_GEQ,
    COMPARE_LET,
    COMPARE_GET,
    COLON,
    IS
  };

  // operators
  extern const Operator T_COMMA;
  extern const Operator T_DOT;
  extern const Operator T_PLUS;
  extern const Operator T_MINUS;
  extern const Operator T_MUL;
  extern const Operator T_DIV;
  extern const Operator T_DECLARE;
  extern const Operator T_ASSIGN;
  extern const Operator T_COMPARE_EQUAL;
  extern const Operator T_COMPARE_NOT_EQUAL;
  extern const Operator T_COMPARE_LEQ;
  extern const Operator T_COMPARE_GEQ;
  extern const Operator T_COMPARE_LET;
  extern const Operator T_COMPARE_GET;
  extern const Operator T_COLON;
  extern const Operator T_IS;

  // Grouping the tokens up
  extern const KeywordVector keywordList;

  extern const OperatorPairVector operatorPairs;
}

#endif
