#pragma once

#include "unit/BasicLaserWeapon.h"
#include "config/GameConfig.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierPistol.h"

namespace unit::soldier::weapon::laser {

/** Soldier laser pistol. */
class SoldierLaserPistol : public BasicLaserWeapon, public ISoldierPistol {
 public:
  /**
   * Creates soldier laser pistol.
   * @param game_config Game process config.
   */
  explicit SoldierLaserPistol(const config::GameConfig &game_config);

};

}
