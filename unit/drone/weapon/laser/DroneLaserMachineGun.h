#pragma once

#include "unit/BasicLaserWeapon.h"
#include "config/GameConfig.h"

#include "../IDroneWeapon.h"
#include "../IDroneMachineGun.h"

namespace unit::drone::weapon::laser {

/** Drone laser machine gun. */
class DroneLaserMachineGun : public BasicLaserWeapon, public IDroneMachineGun {
 public:
  /**
   * Creates drone laser machine gun.
   * @param game_config Game process config.
   */
  explicit DroneLaserMachineGun(const config::GameConfig &game_config);

};

}
