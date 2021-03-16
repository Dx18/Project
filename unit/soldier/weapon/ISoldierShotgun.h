#pragma once

#include "unit/IWeapon.h"

#include "ISoldierWeapon.h"

namespace unit::soldier::weapon {

/** Soldier shotgun common interface. */
class ISoldierShotgun : public ISoldierWeapon {

};

/** Soldier firearm shotgun. */
class SoldierFirearmShotgun : public BasicFirearmWeapon, public ISoldierShotgun {
 public:
  /** Default max ammo for soldier firearm shotgun. */
  static const int kMaxAmmo = 3;
  /** Default mass for soldier firearm shotgun. */
  static const int kMass = 4;

  SoldierFirearmShotgun();

};

/** Soldier laser shotgun. */
class SoldierLaserShotgun : public BasicLaserWeapon, public ISoldierShotgun {
 public:
  /** Default mass for soldier laser shotgun. */
  static const int kMass = 3;

  SoldierLaserShotgun();

};

}
