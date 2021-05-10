#include "Unit.h"

#include "world/script/IWorldScript.h"
#include "world/script/UnitMovingScript.h"
#include "world/script/ProjectileScript.h"

#include "world/World.h"

namespace unit {

Unit::~Unit() = default;

Unit::Unit()
    : name_(""), health_(0), base_health_(0), position_({0.0, 0.0, 0.0}) {

}

Unit::Unit(Unit &&other) noexcept
    : name_(std::move(other.name_)), health_(other.health_), base_health_(other.base_health_),
      position_(other.position_) {

}

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
  return base_health_;
}

void Unit::SetBaseHealth(int base_health) {
  base_health_ = base_health;
}

util::Vector3<double> Unit::Position() const {
  return position_;
}

void Unit::SetPosition(util::Vector3<double> position) {
  position_ = position;
}

world::map::WorldMovementMap Unit::CreateMovementMap(const world::World &world,
                                                     const config::GameConfig &game_config) const {
  return world::map::WorldMovementMap(
      world.Map(),
      world.Map().TilePositionClamped({position_.x, position_.y}),
      MaxTravelDistance(game_config)
  );
}

world::map::WorldVisibilityMap
Unit::CreateVisibilityMap(const world::World &world, const config::GameConfig &game_config) const {
  return world::map::WorldVisibilityMap(
      game_config, world.Map(),
      world.Map().TilePositionClamped({position_.x, position_.y})
  );
}

std::unique_ptr<world::script::IWorldScript>
Unit::CreateMovementScript(size_t unit_id, const world::World &world, const config::GameConfig &game_config,
                           util::Vector3<double> position) {
  world::map::WorldMovementMap movement_map = CreateMovementMap(world, game_config);

  std::optional<std::vector<world::map::WorldMovementMap::PositionInfo>> path = movement_map.Path(
      world.Map().TilePositionClamped({position.x, position.y})
  );
  if (!path.has_value()) {
    return nullptr;
  }

  std::vector<util::Vector3<double>> final_path;
  for (const world::map::WorldMovementMap::PositionInfo &path_position : *path) {
    final_path.push_back({
                             static_cast<double>(path_position.position.x) + 0.5,
                             static_cast<double>(path_position.position.y) + 0.5,
                             0.0
                         });
  }

  return std::make_unique<world::script::UnitMovingScript>(unit_id, final_path, game_config.UnitMoveSpeed());
}

std::unique_ptr<world::script::IWorldScript>
Unit::CreateAttackScript(world::World &world, const config::GameConfig &game_config, size_t target_unit_id) {
  if (!HasActiveWeapon()) {
    return nullptr;
  }

  world::map::WorldVisibilityMap visibility_map = CreateVisibilityMap(world, game_config);

  const unit::Unit &target = world.Entities().GetUnit(target_unit_id);
  util::Vector3<double> target_position = target.Position();
  std::optional<world::map::WorldVisibilityMap::PositionInfo> position
      = visibility_map.GetPositionInfo(world.Map().TilePositionClamped({target_position.x, target_position.y}));
  if (position->visibility > 0.0) {
    size_t projectile_id = world.Entities().CreateProjectile(world::entities::Projectile(
        position_, target_position, game_config.ProjectileMoveSpeed()
    ));

    int damage = target.HasActiveArmor()
                 ? std::max(1, static_cast<int>(ActiveWeapon().BaseDamage()
            / (game_config.DefenceEffect() * target.ActiveArmor().Defence())))
                 : ActiveWeapon().BaseDamage();

    return std::make_unique<world::script::ProjectileScript>(
        projectile_id,
        world::script::ProjectileScript::ProjectileTarget{target_unit_id, damage}
    );
  }

  return nullptr;
}

Unit &Unit::operator=(Unit &&other) noexcept {
  name_.swap(other.name_);
  health_ = other.health_;
  base_health_ = other.base_health_;
  position_ = other.position_;
  return *this;
}

}
