#pragma once

#include "unit/BasicLaserWeapon.h"
#include "config/GameConfig.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierMachineGun.h"

namespace unit::soldier::weapon::laser {

/** Soldier laser machine gun. */
class SoldierLaserMachineGun : public BasicLaserWeapon, public ISoldierMachineGun {
 public:
  /**
   * Creates soldier laser machine gun.
   * @param game_config Game process config.
   */
  explicit SoldierLaserMachineGun(const config::GameConfig &game_config);

};

}
