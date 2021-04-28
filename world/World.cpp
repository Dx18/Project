#include "World.h"

namespace world {

World::World(map::WorldMap map,
             std::vector<std::unique_ptr<unit::Unit>> &&player_units,
             std::vector<std::unique_ptr<unit::Unit>> &&enemy_units)
    : map_(std::move(map)), player_units_(std::move(player_units)), enemy_units_(std::move(enemy_units)) {

}

const map::WorldMap &World::Map() const {
  return map_;
}

const std::vector<std::unique_ptr<unit::Unit>> &World::PlayerUnits() const {
  return player_units_;
}

const std::vector<std::unique_ptr<unit::Unit>> &World::EnemyUnits() const {
  return enemy_units_;
}

}
