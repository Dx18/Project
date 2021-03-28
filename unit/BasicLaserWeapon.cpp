#include "BasicLaserWeapon.h"

namespace unit {

BasicLaserWeapon::BasicLaserWeapon(int mass)
    : mass_(mass) {

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

}
