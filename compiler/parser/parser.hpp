#include "exceptions.hpp"
#include "../lexer/tokens.hpp"
#include "nodes.hpp"

#ifndef PARSER_PARSER_HPP
#define PARSER_PARSER_HPP

namespace parser {

  class Parser {
  public:
    lexer::TokenVector& tokens;
    lexer::TokenVector::iterator token_position;
    Parser(lexer::TokenVector& _tokens) :
      tokens(_tokens), token_position(tokens.begin()) {}

    PBlock* parseBlock();
    PStatement* parseStatement();
    PFunctionDeclaration* parseFunctionDeclaration();
    PReturn* parseReturn();
    PForLoop* parseForLoop();
    PIfElse*parseIfElse();
    PExpression* parseExpression();
    PExpression* parseValue();
    PExpression* parseBaseValue();
    PFunctionCall* parseClassInstantiation();
    PFunctionCall* parseFunctionCall();
    PMethodCall* parseMethodCall(PExpression*);
    PExpressions* parseArguments();
    PExpressions* parseArgumentsParens();

  private:
    void _validateToken(lexer::L type, std::string message);
  };
}

#endif
