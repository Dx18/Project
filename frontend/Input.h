#pragma once

#include <variant>

#include "Key.h"

namespace frontend {

/** User input: typed character or pressed key. */
class Input {
 public:
  /** Creates pressed key input using given key. */
  explicit Input(Key key);
  /** Creates character input using given key. */
  explicit Input(char ch);

  /** Returns true if current input is key input. */
  [[nodiscard]] bool IsKey() const;
  /** Returns pressed key. Throws `std::bad_variant_access` if current input is not key input. */
  [[nodiscard]] Key GetKey() const;

  /** Returns true if current input is character input. */
  [[nodiscard]] bool IsChar() const;
  /** Returns typed character. Throws `std::bad_variant_access` if current input is not character input. */
  [[nodiscard]] char GetChar() const;

 private:
  /** Current value. */
  std::variant<Key, char> value_;

};

}
