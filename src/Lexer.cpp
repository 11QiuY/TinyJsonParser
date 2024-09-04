#include "Lexer.hpp"
#include <cctype>
#include <stdexcept>
#define DEBUG

#ifdef DEBUG
#include <iostream>
#endif

Lexer::Lexer(std::string_view input) : input(input), pos(0) {}

char Lexer::current_char() { return pos < input.size() ? input[pos] : '\0'; }

void Lexer::advance() { pos++; }

void Lexer::skip_whitespace() {
  while (pos < input.size() &&
         std::isspace(static_cast<unsigned char>(current_char()))) {
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
#ifdef DEBUG
  std::cout << "Lexer::string() called and returned " << result << std::endl;
#endif
  return {TokenType::STRING, result};
}

Token Lexer::number() {
  std::string result;
  while (std::isdigit(current_char()) || current_char() == '.') {
    result.push_back(current_char());
    advance();
  }
#ifdef DEBUG
  std::cout << "Lexer::number() called and returned " << result << std::endl;
#endif
  return {TokenType::NUMBER, result};
}

Token Lexer::keyword() {
  std::string result;
  while (std::isalpha(current_char())) {
    result.push_back(current_char());
    advance();
  }
#ifdef DEBUG
  std::cout << "Lexer::keyword() called and returned " << result << std::endl;
#endif
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
      } else if (c == '\0') {
        break;
      } else {
#ifdef DEBUG
        std::cout << "Invalid character: " << c << std::endl;
#endif
        throw std::runtime_error("Invalid character");
      }
    }
    }
  }
  std::cout << "End" << std::endl;

  tokens.push_back({TokenType::END, ""});
  return tokens;
}