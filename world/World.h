#pragma once

#include <memory>
#include <chrono>

#include "unit/Unit.h"

#include "map/WorldMap.h"
#include "entities/WorldEntities.h"
#include "script/IWorldScript.h"

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

  /**
   * Performs world update.
   * @param delta Time passed since previous frame.
   */
  void Update(std::chrono::microseconds delta);

  /**
   * Adds script.
   * @param script Script to add.
   */
  void AddScript(std::unique_ptr<script::IWorldScript> script);

  /** Returns true if all scripts finished their execution. */
  [[nodiscard]] bool ScriptsFinished() const;

 private:
  /** World map. */
  map::WorldMap map_;
  /** World entities. */
  entities::WorldEntities entities_;
  /** Current world scripts. */
  std::vector<std::unique_ptr<script::IWorldScript>> scripts_;

};

}
