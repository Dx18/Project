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

void World::Update(std::chrono::microseconds delta) {
  for (auto &script : scripts_) {
    script->Update(delta, Entities());
  }

  for (size_t i = 0; i < scripts_.size();) {
    if (scripts_[i]->IsCompleted()) {
      std::swap(scripts_[i], scripts_.back());
      scripts_.pop_back();
    } else {
      ++i;
    }
  }
}

void World::AddScript(std::unique_ptr<script::IWorldScript> script) {
  scripts_.push_back(std::move(script));
}

bool World::ScriptsFinished() const {
  return scripts_.empty();
}

}
