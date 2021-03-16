#include "Soldier.h"

namespace unit::soldier {

using namespace unit::soldier::weapon;

Soldier::Soldier()
    : is_primary_weapon_selected_(false) {

}

Soldier::Soldier(Soldier &&other) noexcept
    : Unit(other),
      primary_weapon_(std::move(other.primary_weapon_)),
      secondary_weapon_(std::move(other.secondary_weapon_)),
      is_primary_weapon_selected_(other.is_primary_weapon_selected_) {

}

int Soldier::MaxHealth() const {
  return BaseHealth() + (armor_ ? armor_->Defence() : 0);
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