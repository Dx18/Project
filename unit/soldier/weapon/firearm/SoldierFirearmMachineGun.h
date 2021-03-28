#pragma once

#include "unit/BasicFirearmWeapon.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierMachineGun.h"

namespace unit::soldier::weapon::firearm {

/** Soldier firearm machine gun. */
class SoldierFirearmMachineGun : public BasicFirearmWeapon, public ISoldierMachineGun {
 public:
  /** Default max ammo for soldier firearm machine gun. */
  static const int kMaxAmmo = 5;
  /** Default mass for soldier firearm machine gun. */
  static const int kMass = 5;

  SoldierFirearmMachineGun();

};

}
