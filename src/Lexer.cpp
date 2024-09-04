#include "Lexer.hpp"
#include <cctype>
#include <stdexcept>

Lexer::Lexer(std::string_view input) : input(input), pos(0) {}

char Lexer::current_char() { return pos < input.size() ? input[pos] : '\0'; }

void Lexer::advance() { pos++; }

void Lexer::skip_whitespace() {
  while (pos < input.size() && std::isspace(current_char())) {
    advance();
  }
}

Token Lexer::string() {
  std::string result;
  advance(); // skip the first ' " '
  while (current_char() != '"' && current_char() != '\0') {
    result.push_back(current_char());
    advance();
  }
  advance(); // skip the last ' " '
  return {TokenType::STRING, result};
}

Token Lexer::number() {
  std::string result;
  while (std::isdigit(current_char()) || current_char() == '.') {
    result.push_back(current_char());
    advance();
  }
  return {TokenType::NUMBER, result};
}

Token Lexer::keyword() {
  std::string result;
  while (std::isalpha(current_char())) {
    result.push_back(current_char());
    advance();
  }
  return {result == "true"    ? TokenType::TRUE
          : result == "false" ? TokenType::FALSE
          : result == "null"  ? TokenType::NULL_
                              : TokenType::END,
          result};
}

std::vector<Token> Lexer::tokenize() {
  std::vector<Token> tokens;
  while (current_char() != '\0') {
    skip_whitespace();
    char c = current_char();
    switch (c) {
    case '{':
      tokens.push_back({TokenType::LBRACE, "{"});
      advance();
      break;

    case '}': {
      tokens.push_back({TokenType::RBRACE, "}"});
      advance();
      break;
    }

    case '[': {
      tokens.push_back({TokenType::LBRACKET, "["});
      advance();
      break;
    }

    case ']': {
      tokens.push_back({TokenType::RBRACKET, "]"});
      advance();
      break;
    }

    case ',': {
      tokens.push_back({TokenType::COMMA, ","});
      advance();
      break;
    }

    case ':': {
      tokens.push_back({TokenType::COLON, ":"});
      advance();
      break;
    }

    case '"': {
      tokens.push_back(string());
      break;
    }

    default: {
      if (std::isdigit(c) || c == '-') {
        tokens.push_back(number());
      } else if (std::isalpha(c)) {
        tokens.push_back(keyword());
      } else {
        throw std::runtime_error("Invalid character");
      }
    }
    }
  }

  tokens.push_back({TokenType::END, ""});
  return tokens;
}