#pragma once

#include "unit/BasicLaserWeapon.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierMachineGun.h"

namespace unit::soldier::weapon::laser {

/** Soldier laser machine gun. */
class SoldierLaserMachineGun : public BasicLaserWeapon, public ISoldierMachineGun {
 public:
  /** Default mass for soldier laser machine gun. */
  static const int kMass = 4;

  SoldierLaserMachineGun();

};

}
