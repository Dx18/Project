#pragma once

#include "unit/BasicLaserWeapon.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierPistol.h"

namespace unit::soldier::weapon::laser {

/** Soldier laser pistol. */
class SoldierLaserPistol : public BasicLaserWeapon, public ISoldierPistol {
 public:
  /** Default mass for soldier laser pistol. */
  static const int kMass = 1;

  SoldierLaserPistol();

};

}
