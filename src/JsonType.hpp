#ifndef JSONTYPE_HPP
#define JSONTYPE_HPP

#include <cstddef>
#include <map>
#include <string>
#include <variant>
#include <vector>

struct JSONValue;
using JSONObject = std::map<std::string, JSONValue>;
using JSONArray = std::vector<JSONValue>;

struct JSONValue {
  std::variant<std::nullptr_t, bool, int, double, std::string, JSONObject,
               JSONArray>
      value;

  template <typename T> JSONValue(T value) : value(value) {}
  JSONValue() : value(nullptr) {}
};

#endif