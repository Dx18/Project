#pragma once

#include <memory>

#include "unit/Unit.h"

#include "map/WorldMap.h"
#include "entities/WorldEntities.h"

namespace world {

/** Game world. */
class World {
 public:
  /**
   * Creates game world.
   * @param map World map.
   * @param player_units Player's units.
   * @param enemy_units Enemy's units.
   */
  World(map::WorldMap map,
        std::vector<std::unique_ptr<unit::Unit>> &&player_units,
        std::vector<std::unique_ptr<unit::Unit>> &&enemy_units);

  /** Returns const reference to game world map. */
  const map::WorldMap &Map() const;

  /** Returns reference to game world entities. */
  entities::WorldEntities &Entities();
  /** Returns const reference to game world entities. */
  const entities::WorldEntities &Entities() const;

 private:
  /** World map. */
  map::WorldMap map_;
  /** World entities. */
  entities::WorldEntities entities_;

};

}
