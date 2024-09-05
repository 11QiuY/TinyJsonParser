#include "JsonType.hpp"
#include "Parser.hpp"
#include <iostream>

int main() {
  std::string_view input = R"(
        {
        "name": "Blackmyth Wukong",
        "age": 0.04, 
        "isStudent": false,
        "grades": [10, 8, 6],
        "address": {
            "street": "Shuilian Cave",
            "school": "Nanshanbu continent"
        }
        "job": "god who equals to heaven"
        }   )";

  Parser P(input);
  JSONValue json = P.parse();
  std::cout
      << json["fool"].value()["street"].value().visit<std::string>().value()
      << std::endl;
  return 0;
}