#pragma once

#include "unit/BasicFirearmWeapon.h"
#include "config/GameConfig.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierSniperRifle.h"

namespace unit::soldier::weapon::firearm {

/** Soldier firearm sniper rifle. */
class SoldierFirearmSniperRifle : public BasicFirearmWeapon, public ISoldierSniperRifle {
 public:
  /**
   * Creates soldier firearm sniper rifle.
   * @param game_config Game process config.
   */
  explicit SoldierFirearmSniperRifle(const config::GameConfig &game_config);

};

}
