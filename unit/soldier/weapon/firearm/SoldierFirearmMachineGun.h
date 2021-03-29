#pragma once

#include "unit/BasicFirearmWeapon.h"
#include "config/GameConfig.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierMachineGun.h"

namespace unit::soldier::weapon::firearm {

/** Soldier firearm machine gun. */
class SoldierFirearmMachineGun : public BasicFirearmWeapon, public ISoldierMachineGun {
 public:
  /**
   * Creates soldier firearm machine gun.
   * @param game_config Game process config.
   */
  explicit SoldierFirearmMachineGun(const config::GameConfig &game_config);

};

}
