#include "../exceptions.hpp"
#include "../lexer/tokenizer.hpp"
#include "../parser/parser.hpp"
#include "../yamlast.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;
using namespace lexer;

void mainParseTokens(TokenVector& tokens) {
  auto token_position = tokens.begin();
  auto node = parser::parseStatement(token_position,
                                     tokens.end());
  YAML::Node* yaml = YamlAST::generate(*node);
  // auto node = parser::parseTokens(parser::P2_TRUE_THEN_FALSE, tokens);
  cout << (*yaml) << std::endl;
}

int main(int argc, char* argv[]) {
  string input;
  Tokenizer tokenizer;
  if (argc == 2) {
    string filename(argv[1]);
    ifstream input_stream(filename);
    TokenVector tokens = tokenizer.tokenize(input_stream);
    mainParseTokens(tokens);
  } else {
    cout << "Greyhawk parser." << endl;
    while(true) {
      cout << ">>> ";
      getline(cin, input);
      try {
        istringstream input_stream(input);
        TokenVector tokens = tokenizer.tokenize(input_stream);
        mainParseTokens(tokens);
      } catch (parser::ParserException& e) {
        cout << ((greyhawk::GreyhawkException) e).message << endl;
        continue;
      }
    }
  }
}
