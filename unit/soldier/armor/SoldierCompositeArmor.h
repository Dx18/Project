#pragma once

#include "unit/BasicArmor.h"
#include "config/GameConfig.h"

#include "ISoldierArmor.h"

namespace unit::soldier::armor {

/** Soldier composite armor. */
class SoldierCompositeArmor : public BasicArmor, public ISoldierArmor {
 public:
  /**
   * Creates soldier composite armor.
   * @param game_config Game process config.
   */
  explicit SoldierCompositeArmor(const config::GameConfig &game_config);

};

}
