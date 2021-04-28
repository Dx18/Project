#pragma once

#include <memory>

#include "unit/Unit.h"

#include "map/WorldMap.h"

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
  /** Returns const reference to array of player's units. */
  const std::vector<std::unique_ptr<unit::Unit>> &PlayerUnits() const;
  /** Returns const reference to array of enemy's units. */
  const std::vector<std::unique_ptr<unit::Unit>> &EnemyUnits() const;

 private:
  /** World map. */
  map::WorldMap map_;
  /** Player's units. */
  std::vector<std::unique_ptr<unit::Unit>> player_units_;
  /** Enemy's units. */
  std::vector<std::unique_ptr<unit::Unit>> enemy_units_;

};

}
