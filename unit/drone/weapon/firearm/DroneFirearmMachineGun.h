#pragma once

#include "unit/BasicFirearmWeapon.h"
#include "headquarters_model/tech/Tech.h"

#include "../IDroneWeapon.h"
#include "../IDroneMachineGun.h"

namespace unit::drone::weapon::firearm {

using namespace headquarters_model::tech;

/** Drone firearm machine gun. */
class DroneFirearmMachineGun : public BasicFirearmWeapon, public IDroneMachineGun {
 public:
  /**
   * Creates drone firearm machine gun.
   * @param tech Current tech state.
   */
  explicit DroneFirearmMachineGun(const Tech &tech);

};

}
