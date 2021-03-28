#pragma once

#include "unit/BasicLaserWeapon.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierShotgun.h"

namespace unit::soldier::weapon::laser {

/** Soldier laser shotgun. */
class SoldierLaserShotgun : public BasicLaserWeapon, public ISoldierShotgun {
 public:
  /** Default mass for soldier laser shotgun. */
  static const int kMass = 3;

  SoldierLaserShotgun();

};

}
