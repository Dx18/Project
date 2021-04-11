#pragma once

#include "unit/BasicLaserWeapon.h"
#include "headquarters_model/tech/Tech.h"

#include "../IDroneWeapon.h"
#include "../IDroneMachineGun.h"

namespace unit::drone::weapon::laser {

using namespace headquarters_model::tech;

/** Drone laser machine gun. */
class DroneLaserMachineGun : public BasicLaserWeapon, public IDroneMachineGun {
 public:
  /**
   * Creates drone laser machine gun.
   * @param tech Current tech state.
   */
  explicit DroneLaserMachineGun(const Tech &tech);

};

}
