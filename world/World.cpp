#include "World.h"

namespace world {

World::World(map::WorldMap map,
             std::vector<std::unique_ptr<unit::Unit>> &&player_units,
             std::vector<std::unique_ptr<unit::Unit>> &&enemy_units)
    : map_(std::move(map)), entities_(std::move(player_units), std::move(enemy_units)) {

}

const map::WorldMap &World::Map() const {
  return map_;
}

entities::WorldEntities &World::Entities() {
  return entities_;
}

const entities::WorldEntities &World::Entities() const {
  return entities_;
}

}
