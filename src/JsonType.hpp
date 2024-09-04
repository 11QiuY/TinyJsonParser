#ifndef JSONTYPE_HPP
#define JSONTYPE_HPP

#include <cstddef>
#include <map>
#include <optional>
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

  std::optional<JSONValue> find(std ::string_view key) {
    if (auto obj = std::get_if<JSONObject>(&value); obj != nullptr) {
      auto it = obj->find(key.data());
      if (it != obj->end()) {
        return it->second;
      }
    }
    return std::nullopt;
  }
};

#endif