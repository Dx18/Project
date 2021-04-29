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

class WorldGenerator {
 public:
  explicit WorldGenerator(const config::GameConfig &game_config, std::mt19937 random);

  World GenerateWorld(std::vector<std::unique_ptr<unit::Unit>> &&player_units, double difficulty);

 private:
  const config::GameConfig &game_config_;
  std::mt19937 random_;

  map::WorldMap GenerateMap();
  std::vector<std::unique_ptr<unit::Unit>> GenerateEnemyUnits(double difficulty);

};

}
