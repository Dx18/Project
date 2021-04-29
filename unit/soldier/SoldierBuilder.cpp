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

Soldier SoldierBuilder::Build() {
  Soldier result;
  std::swap(result, current_);
  return result;
}

Unit &SoldierBuilder::CurrentUnit() {
  return current_;
}

}
