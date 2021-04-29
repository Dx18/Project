#include "Drone.h"

namespace unit::drone {

using namespace unit::drone::weapon;

Drone::Drone(Drone &&other) noexcept
    : weapon_(std::move(other.weapon_)) {

}

int Drone::MaxHealth() const {
  return BaseHealth() + (armor_ ? armor_->Defence() : 0);
}

bool Drone::HasWeapon() const {
  return weapon_ != nullptr;
}

const IDroneWeapon *Drone::Weapon() const {
  return weapon_.get();
}

void Drone::SetWeapon(std::unique_ptr<IDroneWeapon> weapon) {
  weapon_ = std::move(weapon);
}

bool Drone::HasArmor() const {
  return armor_ != nullptr;
}

const IDroneArmor *Drone::Armor() const {
  return armor_.get();
}

void Drone::SetArmor(std::unique_ptr<IDroneArmor> armor) {
  armor_ = std::move(armor);
}

Drone &Drone::operator=(Drone &&other) noexcept {
  std::swap(weapon_, other.weapon_);
  return *this;
}

}
