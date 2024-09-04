#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include "JsonType.hpp"
#include "Lexer.hpp"
#include <cstddef>
// #include <stdexcept>
#include <vector>

class Parser {
public:
  Parser(const std::vector<Token> &tokens) : tokens(tokens), pos(0) {}
  JSONValue parse();

private:
  std::vector<Token> tokens;
  size_t pos;
  Token currentToken();
  void advance();
  JSONValue parseValue();
  JSONObject parseObject();
  JSONArray parseArray();
  std::string parseString();
  double parseNumber();
  bool parseBoolean();
  std::nullptr_t parseNull();
};

#endif