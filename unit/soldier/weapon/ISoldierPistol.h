#pragma once

#include "unit/IWeapon.h"

#include "ISoldierWeapon.h"

namespace unit::soldier::weapon {

/** Soldier pistol common interface. */
class ISoldierPistol : public ISoldierWeapon {

};

/** Soldier firearm pistol. */
class SoldierFirearmPistol : public BasicFirearmWeapon, public ISoldierPistol {
 public:
  /** Default max ammo for soldier firearm pistol. */
  static const int kMaxAmmo = 4;
  /** Default mass for soldier firearm pistol. */
  static const int kMass = 2;

  SoldierFirearmPistol();

};

/** Soldier laser pistol. */
class SoldierLaserPistol : public BasicLaserWeapon, public ISoldierPistol {
 public:
  /** Default mass for soldier laser pistol. */
  static const int kMass = 1;

  SoldierLaserPistol();

};

}
