#include "Parser.hpp"
#include "JsonType.hpp"
#include "Lexer.hpp"
#include <stdexcept>

Token Parser::currentToken() {
  return pos < tokens.size() ? tokens[pos] : Token{TokenType::END, ""};
}

void Parser::advance() { pos++; }

JSONValue Parser::parse() { return parseValue(); }

JSONValue Parser::parseValue() {
  Token token = currentToken();
  switch (token.type) {
  case TokenType::LBRACE:
    return parseObject();
  case TokenType::LBRACKET:
    return parseArray();
  case TokenType::STRING:
    return parseString();
  case TokenType::NUMBER:
    return parseNumber();
  case TokenType::TRUE:
    return parseBoolean();
  case TokenType::FALSE:
    return parseBoolean();
  case TokenType::NULL_:
    return parseNull();
  default:
    throw std::runtime_error("Invalid JSON");
  }
}

JSONObject Parser::parseObject() {
  JSONObject object;
  advance(); // skip the '{'
  while (currentToken().type != TokenType::RBRACE) {
    std::string key = parseString();
    advance(); // skip the ':'
    JSONValue value = parseValue();
    object[key] = value;
    if (currentToken().type == TokenType::COMMA) {
      advance(); // skip the ','
    }
  }
  advance(); // skip the '}'
  return object;
}

JSONArray Parser::parseArray() {
  JSONArray array;
  advance(); // skip the '['
  while (currentToken().type != TokenType::RBRACKET) {
    array.push_back(parseValue());
    if (currentToken().type == TokenType::COMMA) {
      advance(); // skip the ','
    }
  }
  advance(); // skip the ']'
  return array;
}

std::string Parser::parseString() {
  std::string value = currentToken().value;
  advance();
  return value;
}

double Parser::parseNumber() {
  double value = std::stod(currentToken().value);
  advance();
  return value;
}

bool Parser::parseBoolean() {
  bool value = currentToken().type == TokenType::TRUE;
  advance();
  return value;
}

std::nullptr_t Parser::parseNull() {
  advance();
  return nullptr;
}