#pragma once

#include "unit/BasicFirearmWeapon.h"
#include "config/GameConfig.h"

#include "../IDroneWeapon.h"
#include "../IDroneMachineGun.h"

namespace unit::drone::weapon::firearm {

/** Drone firearm machine gun. */
class DroneFirearmMachineGun : public BasicFirearmWeapon, public IDroneMachineGun {
 public:
  /**
   * Creates drone firearm machine gun.
   * @param game_config Game process config.
   */
  explicit DroneFirearmMachineGun(const config::GameConfig &game_config);

};

}
