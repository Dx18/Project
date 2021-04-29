#pragma once

#include "config/GameConfig.h"

#include "unit/BasicArmor.h"

#include "ISoldierArmor.h"

namespace unit::soldier::armor {

/** Soldier standard armor. */
class SoldierStandardArmor : public BasicArmor, public ISoldierArmor {
 public:
  /**
   * Creates soldier standard armor.
   * @param game_config Game process config.
   */
  explicit SoldierStandardArmor(const config::GameConfig &game_config);

};

}
