#ifndef JSONLEXER_HPP
#define JSONLEXER_HPP

#include <string>
#include <vector>

enum class TokenType {
  LBRACE,   // {
  RBRACE,   // }
  LBRACKET, // [
  RBRACKET, // ]
  COMMA,    // ,
  COLON,    // :
  STRING,   // "xxx"
  NUMBER,   // 123,123.123
  TRUE,     // true
  FALSE,    // false
  NULL_,    // null
  END,      // ELF
};

struct Token {
  TokenType type;
  std::string value;
};

class Lexer {
public:
  Lexer(std::string_view input);
  std::vector<Token> tokenize();

private:
  std::string_view input;
  size_t pos;
  char current_char();
  void advance();
  void skip_whitespace();
  Token string();
  Token number();
  Token keyword();
};

#endif