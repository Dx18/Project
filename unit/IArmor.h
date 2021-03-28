#pragma once

namespace unit {

/** Common interface for unit armor. */
class IArmor {
 public:
  /** Returns defence of armor. */
  [[nodiscard]] virtual int Defence() const = 0;
  /** Returns mass of armor. */
  [[nodiscard]] virtual int Mass() const = 0;

};

}
