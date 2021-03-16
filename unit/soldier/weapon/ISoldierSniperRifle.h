#pragma once

#include "unit/IWeapon.h"

#include "ISoldierWeapon.h"

namespace unit::soldier::weapon {

/** Soldier sniper rifle common interface. */
class ISoldierSniperRifle : public ISoldierWeapon {

};

/** Soldier firearm sniper rifle. */
class SoldierFirearmSniperRifle : public BasicFirearmWeapon, public ISoldierSniperRifle {
 public:
  /** Default max ammo for soldier firearm sniper rifle. */
  static const int kMaxAmmo = 3;
  /** Default mass for soldier firearm sniper rifle. */
  static const int kMass = 4;

  SoldierFirearmSniperRifle();

};

/** Soldier laser sniper rifle. */
class SoldierLaserSniperRifle : public BasicLaserWeapon, public ISoldierSniperRifle {
 public:
  /** Default mass for soldier laser sniper rifle. */
  static const int kMass = 3;

  SoldierLaserSniperRifle();

};

}
