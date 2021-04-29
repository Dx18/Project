#pragma once

#include "unit/BasicArmor.h"
#include "config/GameConfig.h"

#include "IDroneArmor.h"

namespace unit::drone::armor {

/** Drone standard armor. */
class DroneStandardArmor : public BasicArmor, public IDroneArmor {
 public:
  /**
   * Creates drone standard armor.
   * @param game_config Game process config.
   */
  explicit DroneStandardArmor(const config::GameConfig &game_config);

};

}
