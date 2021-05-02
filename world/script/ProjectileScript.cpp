#include "ProjectileScript.h"

namespace world::script {

ProjectileScript::ProjectileScript(size_t projectile_id, std::optional<ProjectileTarget> target)
    : projectile_id_(projectile_id), target_(target), is_completed_(false) {

}

void ProjectileScript::Update(std::chrono::microseconds delta, entities::WorldEntities &entities) {
  if (IsCompleted()) {
    return;
  }

  if (!entities.IsProjectileAlive(projectile_id_)) {
    if (target_.has_value()) {
      size_t unit_id = target_->unit_id;
      int damage = target_->damage;

      unit::Unit &unit = entities.GetUnit(unit_id);
      unit.SetHealth(std::max(unit.Health() - damage, 0));
    }
    is_completed_ = true;
  }
}

bool ProjectileScript::IsCompleted() const {
  return is_completed_;
}

}
