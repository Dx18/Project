#pragma once

#include "unit/BasicFirearmWeapon.h"

#include "../IDroneWeapon.h"
#include "../IDroneMachineGun.h"

namespace unit::drone::weapon::firearm {

/** Drone firearm machine gun. */
class DroneFirearmMachineGun : public BasicFirearmWeapon, public IDroneMachineGun {
 public:
  /** Default max ammo for drone firearm machine gun. */
  static const int kMaxAmmo = 5;
  /** Default mass for drone firearm machine gun. */
  static const int kMass = 4;

  DroneFirearmMachineGun();

};

}
