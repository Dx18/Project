#include "SoldierBuilder.h"

namespace unit::soldier {

SoldierBuilder &SoldierBuilder::WithPrimaryWeapon(std::unique_ptr<ISoldierWeapon> weapon) {
  current_.SetPrimaryWeapon(std::move(weapon));
  return *this;
}

SoldierBuilder &SoldierBuilder::WithSecondaryWeapon(std::unique_ptr<ISoldierWeapon> weapon) {
  current_.SetSecondaryWeapon(std::move(weapon));
  return *this;
}

SoldierBuilder &SoldierBuilder::WithArmor(std::unique_ptr<ISoldierArmor> armor) {
  current_.SetArmor(std::move(armor));
  return *this;
}

const ISoldierWeapon *SoldierBuilder::PrimaryWeapon() const {
  return current_.PrimaryWeapon();
}

const ISoldierWeapon *SoldierBuilder::SecondaryWeapon() const {
  return current_.SecondaryWeapon();
}

const ISoldierArmor *SoldierBuilder::Armor() const {
  return current_.Armor();
}

Soldier SoldierBuilder::Build() {
  Soldier result;
  std::swap(result, current_);
  return result;
}

Unit &SoldierBuilder::CurrentUnit() {
  return current_;
}

const Unit &SoldierBuilder::CurrentUnit() const {
  return current_;
}

}
