#include "BasicFirearmWeapon.h"

namespace unit {

BasicFirearmWeapon::BasicFirearmWeapon(int ammo, int max_ammo, int mass)
    : ammo_(ammo), max_ammo_(max_ammo), mass_(mass) {

}

std::optional<int> BasicFirearmWeapon::ShotsLeft() const {
  return ammo_;
}

std::optional<int> BasicFirearmWeapon::MaxShots() const {
  return max_ammo_;
}

int BasicFirearmWeapon::Mass() const {
  return mass_;
}

bool BasicFirearmWeapon::CanBeReloaded() const {
  return true;
}

void BasicFirearmWeapon::Reload() {
  ammo_ = max_ammo_;
}

}
