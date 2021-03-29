#pragma once

#include "unit/BasicLaserWeapon.h"
#include "config/GameConfig.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierShotgun.h"

namespace unit::soldier::weapon::laser {

/** Soldier laser shotgun. */
class SoldierLaserShotgun : public BasicLaserWeapon, public ISoldierShotgun {
 public:
  /**
   * Creates soldier laser shotgun.
   * @param game_config Game process config.
   */
  explicit SoldierLaserShotgun(const config::GameConfig &game_config);

};

}
