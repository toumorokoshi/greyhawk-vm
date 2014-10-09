#include "parser.hpp"

using namespace VM;
using namespace lexer;

#define debug(s);
// #define debug(s) std::cout << s << std::endl;

namespace parser {

  bool isBinaryOperator(const Token& token) {
    return token.type >= PLUS && token.type <= IS;
  }

  PExpression* Parser::parseExpression() {
    // an expression could be one of the following:
    // * a method call
    // * a value
    // * an array access
    // a binary operator
    // all of the start with a base value.
    auto lhs = parseValue();

    while (token_position != tokens.end() && isBinaryOperator(**token_position)) {
      auto op = (*token_position)->type;
      token_position++;
      auto rhs = parseValue();
      lhs = new PBinaryOperation(lhs, op, rhs);
    }

    return lhs;
  }

  PExpression* Parser::parseValue() {
    auto baseValue = parseBaseValue();

    while (true) {
      debug("loop");

      if (token_position == tokens.end()) {
        return baseValue;
      }

      // now we check to see if we're
      // accessing an array or it's function call
      switch((*token_position)->type) {
      case DOT:
        baseValue = parseMethodCall(baseValue);
        break;
      case L_BRACKET:
        baseValue = parseArrayAccess(baseValue);
        break;
      default:
        return baseValue;
      }
    }
  }

  PMethodCall* Parser::parseMethodCall(PExpression* currentValue) {
    debug("parseMethodCall");

    debug("parseMethodCall: top of the while");

    _validateToken(DOT, "expected a . for a method call");
    token_position++;

    _validateToken(IDENTIFIER, "expected an identifier for a method call");
    debug("parsing identifier...");
    auto methodName = (*token_position)->value;
    token_position++;

    PExpressions* arguments;

    if (token_position != tokens.end() && (*token_position)->type == LPAREN) {
      debug("parseMethodCall: found method call, creating VMCallMethod..");
      arguments = parseArgumentsParens();

    } else {
      // this is something like a.foo,
      // which directly translates to a.foo()
      debug("parseMethodCall: found property, implicitly creating VMCallMethod..");
      arguments = new PExpressions;
    }

    debug("parseMethodCall: finished");

    return new PMethodCall(currentValue, methodName, *arguments);
  }

  PCall* Parser::parseCall() {
    debug("parseCall");

    _validateToken(IDENTIFIER, "expected an identifier for a function call");
    auto name = (*token_position)->value;
    token_position++;

    PExpressions* arguments = parseArgumentsParens();
    debug("finished parseCall");
    return new PCall(name, *arguments);
  }

  PMethodCall* Parser::parseArrayAccess(PExpression* value) {
    debug("parseArrayAccess");

    _validateToken(L_BRACKET, "expected an '[' for an array access");
    token_position++;

    auto expression = parseExpression();

    _validateToken(R_BRACKET, "expected an ']' for an array access");
    token_position++;

    debug("parseArrayAccess: finished");
    return new PMethodCall(value, "__get", *new PExpressions{expression});
  }

  PExpression* Parser::parseBaseValue() {
    debug("parseBaseValue");
    auto token = *token_position;
    token_position++;
    switch(token->type) {

    case L_BRACKET:
      debug("parseBaseValue: return array.");
      token_position--;
      return parseArray();

    case TYPE:
      debug("parseBaseValue: returning class.");
      token_position--;
      return parseClassInstantiation();

    case STRING:
      debug("parseBaseValue: returning string.");
      return new PConstantString(token->value);

    case INT:
      debug("parseBaseValue: returning int.");
      return new PConstantInt(std::stoi(token->value));

    case IDENTIFIER: {
      debug("parseBaseValue: return identifier.");

      if ((*token_position)->type == LPAREN) {
        token_position--;
        return parseCall();
      } else {
        return new PIdentifier(token->value);
      }
    }

    case TRUE:
      debug("parseBaseValue: return true.");
      return new PConstantBool(true);

    case FALSE:
      debug("parseBaseValue: return false.");
      return new PConstantBool(false);

    default:
      throw ParserException(*token, "expected value!");
    }
  }

  PExpressions* Parser::parseArguments() {
    auto arguments = new PExpressions();

    while ((*token_position)->type != RPAREN) {
      arguments->push_back(parseExpression());
      if ((*token_position)->type != RPAREN) {
        if ((*token_position)->type != COMMA) {
          throw ParserException(**token_position,
                                "expected a ',' in between arguments.");
        }
        token_position++;
      }
    }

    debug("parseArguments: finished");
    return arguments;
  }

  PExpressions* Parser::parseArgumentsParens() {

    _validateToken(LPAREN, "expected a '(' for a method call!");
    token_position++; // iterate past a left paren

    auto arguments = parseArguments();

    _validateToken(RPAREN, "expected a ')' for a method call!");
    token_position++; // iterat past a right paren

    return arguments;
  }

}
