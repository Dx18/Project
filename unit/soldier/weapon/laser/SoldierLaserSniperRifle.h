#pragma once

#include "unit/BasicLaserWeapon.h"
#include "config/GameConfig.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierSniperRifle.h"

namespace unit::soldier::weapon::laser {

/** Soldier laser sniper rifle. */
class SoldierLaserSniperRifle : public BasicLaserWeapon, public ISoldierSniperRifle {
 public:
  /**
   * Creates soldier laser sniper rifle.
   * @param game_config Game process config.
   */
  explicit SoldierLaserSniperRifle(const config::GameConfig &game_config);

};

}
