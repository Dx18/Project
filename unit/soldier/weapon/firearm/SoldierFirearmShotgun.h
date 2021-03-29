#pragma once

#include "unit/BasicFirearmWeapon.h"
#include "config/GameConfig.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierShotgun.h"

namespace unit::soldier::weapon::firearm {

/** Soldier firearm shotgun. */
class SoldierFirearmShotgun : public BasicFirearmWeapon, public ISoldierShotgun {
 public:
  /**
   * Creates soldier firearm shotgun.
   * @param game_config Game process config.
   */
  explicit SoldierFirearmShotgun(const config::GameConfig &game_config);

};

}
