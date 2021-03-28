#pragma once

#include "unit/BasicFirearmWeapon.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierPistol.h"

namespace unit::soldier::weapon::firearm {

/** Soldier firearm pistol. */
class SoldierFirearmPistol : public BasicFirearmWeapon, public ISoldierPistol {
 public:
  /** Default max ammo for soldier firearm pistol. */
  static const int kMaxAmmo = 4;
  /** Default mass for soldier firearm pistol. */
  static const int kMass = 2;

  SoldierFirearmPistol();

};

}
