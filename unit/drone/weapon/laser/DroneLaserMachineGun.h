#pragma once

#include "unit/BasicLaserWeapon.h"

#include "../IDroneWeapon.h"
#include "../IDroneMachineGun.h"

namespace unit::drone::weapon::laser {

/** Drone laser machine gun. */
class DroneLaserMachineGun : public BasicLaserWeapon, public IDroneMachineGun {
 public:
  /** Default mass for drone laser machine gun. */
  static const int kMass = 3;

  DroneLaserMachineGun();

};

}
