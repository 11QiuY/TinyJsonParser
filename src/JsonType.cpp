#include "JsonType.hpp"
#include <iostream>

std::optional<JSONValue> JSONValue::operator[](const std::string &key) {
  if (auto obj = std::get_if<JSONObject>(&value)) {
    if (auto it = obj->find(key); it != obj->end()) {
      return it->second;
    }
  }
  std::cout << "Invalid type\n";
  return std::nullopt;
}
std::optional<JSONValue> JSONValue::operator[](const size_t index) {
  if (auto arr = std::get_if<JSONArray>(&value)) {
    if (index < arr->size()) {
      return (*arr)[index];
    } else {
      std::cout << "Index out of range\n";
    }
  }
  std::cout << "Invalid type\n";
  return std::nullopt;
}