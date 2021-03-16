#include "Unit.h"

namespace unit {

Unit::~Unit() = default;

const std::string &Unit::Name() const {
  return name_;
}

void Unit::SetName(const std::string &name) {
  name_ = name;
}

int Unit::Health() const {
  return health_;
}

void Unit::SetHealth(int health) {
  health_ = health;
}

int Unit::BaseHealth() const {
  return max_health_;
}

void Unit::SetBaseHealth(int base_health) {
  max_health_ = base_health;
}

util::Vector3<double> Unit::Position() const {
  return position_;
}

void Unit::SetPosition(util::Vector3<double> position) {
  position_ = position;
}

}
