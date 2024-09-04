#include "JsonType.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

int main() {
  std::string_view input = R"(
        {
        "name": "John Doe",
        "age": 30,
        "isStudent": false,
        "grades": [90, 80, 85],
        "address": {
            "street": "123 Main St",
            "city": "New York"
        }
        }
    )";

  Lexer lexer(input);
  auto tokens = lexer.tokenize();
  Parser parser(tokens);
  JSONValue json = parser.parse();
  return 0;
}