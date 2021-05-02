#include "Drone.h"

namespace unit::drone {

using namespace unit::drone::weapon;

Drone::Drone(Drone &&other) noexcept
    : Unit(std::move(other)),
      weapon_(std::move(other.weapon_)) {

}

int Drone::MaxHealth() const {
  return BaseHealth() + (armor_ ? armor_->Defence() : 0);
}

int Drone::MaxTravelDistance(const config::GameConfig &game_config) const {
  int mass = 0;
  if (weapon_) {
    mass += weapon_->Mass();
  }
  if (armor_) {
    mass += armor_->Mass();
  }
  return util::math::clamp(
      game_config.BaseDroneTravelDistanceLimit() - mass,
      game_config.MinDroneTravelDistanceLimit(),
      game_config.MaxDroneTravelDistanceLimit()
  );
}

bool Drone::HasActiveWeapon() const {
  return weapon_ != nullptr;
}

const IWeapon &Drone::ActiveWeapon() const {
  return *weapon_;
}

bool Drone::HasActiveArmor() const {
  return armor_ != nullptr;
}

const IArmor &Drone::ActiveArmor() const {
  return *armor_;
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
  static_cast<Unit &>(*this) = std::move(other);
  std::swap(weapon_, other.weapon_);
  return *this;
}

}
