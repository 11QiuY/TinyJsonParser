#ifndef JSONTYPE_HPP
#define JSONTYPE_HPP

#include <cstddef>
#include <map>
#include <stdexcept>
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

  template <typename T> JSONValue(T value) {
    if constexpr (check_type<T>()) {
      this->value = value;
    } else {
      throw std::invalid_argument("Invalid type");
    }
  }

  JSONValue() : value(nullptr) {}

  template <typename T> T &get() { return std::get<T>(value); }

  template <typename T> bool is() { return std::holds_alternative<T>(value); }

  template <typename T> constexpr bool check_type() const {
    using K = std::decay_t<T>;
    return std::is_same_v<K, std::nullptr_t> || std::is_same_v<K, bool> ||
           std::is_same_v<K, int> || std::is_same_v<K, double> ||
           std::is_same_v<K, std::string> || std::is_same_v<K, JSONObject> ||
           std::is_same_v<K, JSONArray>;
  }
};

#endif