#include "../vm/vm.hpp"
#include "exceptions.hpp"
#include "../lexer/tokens.hpp"

#ifndef PARSER_PARSER_HPP
#define PARSER_PARSER_HPP

namespace parser {

  class Parser {
  public:
    VM::VMScope* scope;
    lexer::TokenVector::iterator& token_position;
    lexer::TokenVector& tokens;
    Parser(VM::VMScope* _scope,
           lexer::TokenVector::iterator& _token_position,
           lexer::TokenVector& _tokens) :
      scope(_scope), token_position(_token_position), tokens(_tokens) {}

    VM::VMBlock* parseBlock();
    VM::VMStatement* parseStatement();
    VM::VMExpression* parseExpression();
    VM::VMExpression* parseValue();
    VM::VMExpression* parseClassInstantiation();
    VM::VMCall* parseCall();
    VM::VMCallMethod* parseMethodCall();
    std::vector<VM::VMExpression*>* parseArguments();
    std::vector<VM::VMExpression*>* parseArgumentsParens();

  private:
    void _validateToken(lexer::L type, std::string message);
  };
}

#endif
