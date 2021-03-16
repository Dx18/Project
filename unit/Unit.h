#pragma once

#include <string>

#include "util/Vector.h"

namespace unit {

/** Unit. */
class Unit {
 public:
  virtual ~Unit() = 0;

  /** Returns name of unit. */
  [[nodiscard]] const std::string &Name() const;
  /**
   * Sets name of unit.
   * @param name Name to set.
   */
  void SetName(const std::string &name);

  /** Returns health of unit. */
  [[nodiscard]] int Health() const;
  /**
   * Sets health of unit.
   * @param health Health to set.
   */
  void SetHealth(int health);

  /** Returns base health of unit. */
  [[nodiscard]] int BaseHealth() const;
  /**
   * Sets base health of unit.
   * @param base_health Base health to set.
   */
  void SetBaseHealth(int base_health);

  /** Returns max health of unit. */
  [[nodiscard]] virtual int MaxHealth() const = 0;

  /** Returns position of unit. */
  [[nodiscard]] util::Vector3<double> Position() const;
  /**
   * Sets position of unit.
   * @param position Position to set.
   */
  void SetPosition(util::Vector3<double> position);

 private:
  /** Name of unit. */
  std::string name_;
  /** Health of unit. */
  int health_;
  /** Max health of unit. */
  int max_health_;
  /** Current position of unit. */
  util::Vector3<double> position_;

};

}
