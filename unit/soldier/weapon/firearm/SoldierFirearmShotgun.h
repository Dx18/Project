#pragma once

#include "unit/BasicFirearmWeapon.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierShotgun.h"

namespace unit::soldier::weapon::firearm {

/** Soldier firearm shotgun. */
class SoldierFirearmShotgun : public BasicFirearmWeapon, public ISoldierShotgun {
 public:
  /** Default max ammo for soldier firearm shotgun. */
  static const int kMaxAmmo = 3;
  /** Default mass for soldier firearm shotgun. */
  static const int kMass = 4;

  SoldierFirearmShotgun();

};

}
