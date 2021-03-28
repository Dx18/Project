#pragma once

#include "unit/BasicFirearmWeapon.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierSniperRifle.h"

namespace unit::soldier::weapon::firearm {

/** Soldier firearm sniper rifle. */
class SoldierFirearmSniperRifle : public BasicFirearmWeapon, public ISoldierSniperRifle {
 public:
  /** Default max ammo for soldier firearm sniper rifle. */
  static const int kMaxAmmo = 3;
  /** Default mass for soldier firearm sniper rifle. */
  static const int kMass = 4;

  SoldierFirearmSniperRifle();

};

}
