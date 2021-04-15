#pragma once

#include "Unit.h"

namespace unit {

/**
 * Unit builder.
 * @tparam Builder Type of inherited builder.
 */
template<typename Builder>
class UnitBuilder {
 public:
  virtual ~UnitBuilder() = 0;

  /**
   * Sets name of unit and returns current builder.
   * @param name Name to set.
   */
  Builder &WithName(const std::string &name);
  /**
   * Sets health of unit and returns current builder.
   * @param health Health to set.
   */
  Builder &WithHealth(int health);
  /**
   * Sets base health of unit and returns current builder.
   * @param base_health Base health to set.
   */
  Builder &WithBaseHealth(int base_health);
  /**
   * Sets position of unit and returns current builder.
   * @param position Position to set.
   */
  Builder &WithPosition(util::Vector3<double> position);

  /** Returns current name of unit. */
  [[nodiscard]] const std::string &Name() const;
  /** Returns current health of unit. */
  [[nodiscard]] int Health() const;
  /** Returns current base health of unit. */
  [[nodiscard]] int BaseHealth() const;
  /** Returns current position of unit. */
  [[nodiscard]] util::Vector3<double> Position() const;

 protected:
  /** Returns reference to current constructed unit. */
  virtual Unit &CurrentUnit() = 0;

};

template<typename Builder>
UnitBuilder<Builder>::~UnitBuilder() = default;

template<typename Builder>
Builder &UnitBuilder<Builder>::WithName(const std::string &name) {
  CurrentUnit().SetName(name);
  return *this;
}

template<typename Builder>
Builder &UnitBuilder<Builder>::WithHealth(int health) {
  CurrentUnit().SetHealth(health);
  return *this;
}

template<typename Builder>
Builder &UnitBuilder<Builder>::WithBaseHealth(int base_health) {
  CurrentUnit().SetBaseHealth(base_health);
  return *this;
}

template<typename Builder>
Builder &UnitBuilder<Builder>::WithPosition(util::Vector3<double> position) {
  CurrentUnit().SetPosition(position);
  return *this;
}

template<typename Builder>
const std::string &UnitBuilder<Builder>::Name() const {
  return CurrentUnit().Name();
}

template<typename Builder>
int UnitBuilder<Builder>::Health() const {
  return CurrentUnit().Health();
}

template<typename Builder>
int UnitBuilder<Builder>::BaseHealth() const {
  return CurrentUnit().BaseHealth();
}

template<typename Builder>
util::Vector3<double> UnitBuilder<Builder>::Position() const {
  return CurrentUnit().Position();
}

}
