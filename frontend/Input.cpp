#include "Input.h"

namespace frontend {

Input::Input(Key key)
    : value_(key) {

}

Input::Input(char ch)
    : value_(ch) {

}

bool Input::IsKey() const {
  return std::holds_alternative<Key>(value_);
}

Key Input::GetKey() const {
  return std::get<Key>(value_);
}

bool Input::IsChar() const {
  return std::holds_alternative<char>(value_);
}

char Input::GetChar() const {
  return std::get<char>(value_);
}

}
