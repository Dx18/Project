#pragma once

#include "unit/BasicLaserWeapon.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierSniperRifle.h"

namespace unit::soldier::weapon::laser {

/** Soldier laser sniper rifle. */
class SoldierLaserSniperRifle : public BasicLaserWeapon, public ISoldierSniperRifle {
 public:
  /** Default mass for soldier laser sniper rifle. */
  static const int kMass = 3;

  SoldierLaserSniperRifle();

};

}
