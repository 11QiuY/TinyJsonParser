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
  auto dic = json.get<JSONObject>();
  auto grades = dic.at("grades").get<JSONArray>();
  for (auto grade : grades) {
    std::cout << grade.get<double>() << std::endl;
  }
  return 0;
}