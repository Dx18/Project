#pragma once

#include "unit/BasicFirearmWeapon.h"
#include "config/GameConfig.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierPistol.h"

namespace unit::soldier::weapon::firearm {

/** Soldier firearm pistol. */
class SoldierFirearmPistol : public BasicFirearmWeapon, public ISoldierPistol {
 public:
  /**
   * Creates soldier firearm pistol.
   * @param game_config Game process config.
   */
  explicit SoldierFirearmPistol(const config::GameConfig &game_config);

};

}
