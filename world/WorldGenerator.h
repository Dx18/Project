#pragma once

#include <random>

#include "config/GameConfig.h"
#include "headquarters_model/tech/Tech.h"
#include "unit/soldier/SoldierBuilder.h"
#include "unit/soldier/weapon/ISoldierWeaponFactory.h"
#include "unit/soldier/weapon/firearm/SoldierFirearmWeaponFactory.h"
#include "unit/soldier/weapon/laser/SoldierLaserWeaponFactory.h"
#include "unit/soldier/armor/ISoldierArmorFactory.h"
#include "unit/soldier/armor/standard/SoldierStandardArmorFactory.h"
#include "unit/soldier/armor/composite/SoldierCompositeArmorFactory.h"
#include "unit/drone/DroneBuilder.h"
#include "unit/drone/weapon/IDroneWeaponFactory.h"
#include "unit/drone/weapon/firearm/DroneFirearmWeaponFactory.h"
#include "unit/drone/weapon/laser/DroneLaserWeaponFactory.h"
#include "unit/drone/armor/IDroneArmorFactory.h"
#include "unit/drone/armor/standard/DroneStandardArmorFactory.h"
#include "unit/drone/armor/composite/DroneCompositeArmorFactory.h"

#include "World.h"

namespace world {

/** World generator. */
class WorldGenerator {
 public:
  /**
   * Creates world generator.
   * @param game_config Const reference to game config.
   * @param random Random number generator.
   */
  explicit WorldGenerator(const config::GameConfig &game_config, std::mt19937 random);

  /**
   * Generates world (world map and enemy units), places all units on map and returns generated world. Difficulty has
   * influence on number of units, their tech and their weapons and armor.
   * @param player_units Player's units.
   * @param difficulty Difficulty.
   */
  World GenerateWorld(std::vector<std::unique_ptr<unit::Unit>> &&player_units, double difficulty);

 private:
  /** Const reference to game config. */
  const config::GameConfig &game_config_;
  /** Random number generation. */
  std::mt19937 random_;

  /** Generates map. */
  map::WorldMap GenerateMap();
  /**
   * Generates enemy's units using given difficulty.
   * @param difficulty Difficulty.
   */
  std::vector<std::unique_ptr<unit::Unit>> GenerateEnemyUnits(double difficulty);

};

}
