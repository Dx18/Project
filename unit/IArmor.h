#pragma once

namespace unit {

/** Common interface for unit armor. */
class IArmor {
 public:
  /** Virtual destructor. */
  virtual ~IArmor() = 0;

  /** Returns defence of armor. */
  [[nodiscard]] virtual int Defence() const = 0;
  /** Returns mass of armor. */
  [[nodiscard]] virtual int Mass() const = 0;

};

}
