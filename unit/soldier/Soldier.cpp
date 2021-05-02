#include "Soldier.h"

namespace unit::soldier {

using namespace unit::soldier::weapon;

Soldier::Soldier()
    : is_primary_weapon_selected_(true) {

}

Soldier::Soldier(Soldier &&other) noexcept
    : Unit(std::move(other)),
      primary_weapon_(std::move(other.primary_weapon_)),
      secondary_weapon_(std::move(other.secondary_weapon_)),
      is_primary_weapon_selected_(other.is_primary_weapon_selected_) {

}

int Soldier::MaxHealth() const {
  return BaseHealth() + (armor_ ? armor_->Defence() : 0);
}

int Soldier::MaxTravelDistance(const config::GameConfig &game_config) const {
  int mass = 0;
  if (primary_weapon_) {
    mass += primary_weapon_->Mass();
  }
  if (secondary_weapon_) {
    mass += secondary_weapon_->Mass();
  }
  if (armor_) {
    mass += armor_->Mass();
  }
  return util::math::clamp(
      game_config.BaseSoldierTravelDistanceLimit() - mass,
      game_config.MinSoldierTravelDistanceLimit(),
      game_config.MaxSoldierTravelDistanceLimit()
  );
}

bool Soldier::HasActiveWeapon() const {
  return is_primary_weapon_selected_ ? primary_weapon_ != nullptr : secondary_weapon_ != nullptr;
}

const IWeapon &Soldier::ActiveWeapon() const {
  return is_primary_weapon_selected_ ? *primary_weapon_ : *secondary_weapon_;
}

bool Soldier::HasActiveArmor() const {
  return armor_ != nullptr;
}

const IArmor &Soldier::ActiveArmor() const {
  return *armor_;
}

bool Soldier::HasPrimaryWeapon() const {
  return primary_weapon_ != nullptr;
}

const ISoldierWeapon *Soldier::PrimaryWeapon() const {
  return primary_weapon_.get();
}

void Soldier::SetPrimaryWeapon(std::unique_ptr<ISoldierWeapon> weapon) {
  primary_weapon_ = std::move(weapon);
}

bool Soldier::HasSecondaryWeapon() const {
  return secondary_weapon_ != nullptr;
}

const ISoldierWeapon *Soldier::SecondaryWeapon() const {
  return secondary_weapon_.get();
}

void Soldier::SetSecondaryWeapon(std::unique_ptr<ISoldierWeapon> weapon) {
  secondary_weapon_ = std::move(weapon);
}

bool Soldier::IsPrimaryWeaponSelected() const {
  return is_primary_weapon_selected_;
}

void Soldier::SelectWeapon(bool primary) {
  is_primary_weapon_selected_ = primary;
}

void Soldier::ToggleWeapon() {
  SelectWeapon(!is_primary_weapon_selected_);
}

Soldier &Soldier::operator=(Soldier &&other) noexcept {
  static_cast<Unit &>(*this) = std::move(other);
  std::swap(primary_weapon_, other.primary_weapon_);
  std::swap(secondary_weapon_, other.secondary_weapon_);
  std::swap(is_primary_weapon_selected_, other.is_primary_weapon_selected_);
  return *this;
}

bool Soldier::HasArmor() const {
  return armor_ != nullptr;
}

const ISoldierArmor *Soldier::Armor() const {
  return armor_.get();
}

void Soldier::SetArmor(std::unique_ptr<ISoldierArmor> armor) {
  armor_ = std::move(armor);
}

}
