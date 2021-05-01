#include "Unit.h"

#include "world/script/IWorldScript.h"
#include "world/script/UnitMovingScript.h"

namespace unit {

Unit::~Unit() = default;

const std::string &Unit::Name() const {
  return name_;
}

void Unit::SetName(const std::string &name) {
  name_ = name;
}

int Unit::Health() const {
  return health_;
}

void Unit::SetHealth(int health) {
  health_ = health;
}

int Unit::BaseHealth() const {
  return max_health_;
}

void Unit::SetBaseHealth(int base_health) {
  max_health_ = base_health;
}

util::Vector3<double> Unit::Position() const {
  return position_;
}

void Unit::SetPosition(util::Vector3<double> position) {
  position_ = position;
}

std::unique_ptr<world::script::IWorldScript>
Unit::CreateMovementScript(size_t unit_id, const world::map::WorldMap &map, const config::GameConfig &game_config,
                           util::Vector3<double> position) {
  using namespace world::map;
  using namespace world::script;

  util::Vector2<size_t> map_size = map.Size();
  auto tile_position = [map_size](const util::Vector3<double> &position) {
    return util::Vector2<size_t>{
        static_cast<size_t>(util::math::clamp(
            std::floor(position.x), 0.0, static_cast<double>(map_size.x - 1)
        )),
        static_cast<size_t>(util::math::clamp(
            std::floor(position.y), 0.0, static_cast<double>(map_size.y - 1)
        )),
    };
  };

  WorldMovementMap movement_map(map, tile_position(position_), MaxTravelDistance(game_config));

  std::optional<std::vector<WorldMovementMap::PositionInfo>> path = movement_map.Path(tile_position(position));
  if (!path.has_value()) {
    return nullptr;
  }

  std::vector<util::Vector3<double>> final_path;
  for (const WorldMovementMap::PositionInfo &path_position : *path) {
    final_path.push_back({
                             static_cast<double>(path_position.position.x) + 0.5,
                             static_cast<double>(path_position.position.y) + 0.5,
                             0.0
                         });
  }

  return std::make_unique<UnitMovingScript>(unit_id, final_path, game_config.UnitMoveSpeed());
}

}
