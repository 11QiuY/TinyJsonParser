#include "JsonType.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include <iostream>

int main() {
  std::string_view input = R"(
        {
        "name": "Blackmyth Wukong",
        "age": 0.04, 
    00    "isStudent": false,
        "grades": [10, 8, 6],
        "address": {
            "street": "Shuilian Cave",
            "school": "Nanshanbu continent"
        }
        "job": "god who equals to heaven"
        }   )";

  Lexer lexer(input);
  auto tokens = lexer.tokenize();
  Parser parser(tokens);
  JSONValue json = parser.parse();
  auto x = json.find("job");
  if (x) {
    std::cout << "job: " << std::get<std::string>(x->value) << std::endl;
  }
  return 0;
}