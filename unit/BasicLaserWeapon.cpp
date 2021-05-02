#include "BasicLaserWeapon.h"

namespace unit {

BasicLaserWeapon::BasicLaserWeapon(int mass, int base_damage)
    : mass_(mass), base_damage_(base_damage) {

}

std::optional<int> BasicLaserWeapon::ShotsLeft() const {
  return {};
}

std::optional<int> BasicLaserWeapon::MaxShots() const {
  return {};
}

int BasicLaserWeapon::Mass() const {
  return mass_;
}

bool BasicLaserWeapon::CanBeReloaded() const {
  return false;
}

void BasicLaserWeapon::Reload() {

}

int BasicLaserWeapon::BaseDamage() const {
  return base_damage_;
}

}
