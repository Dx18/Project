#pragma once

#include "world/entities/Projectile.h"

#include "IWorldScript.h"

namespace world::script {

/** Projectile script. */
class ProjectileScript : public IWorldScript {
 public:
  /** Target of projectile. */
  struct ProjectileTarget {
    /** ID of unit that will be damaged by projectile. */
    size_t unit_id;
    /** Calculated damage of projectile. */
    int damage;
  };

  /**
   * Creates projectile script.
   * @param projectile_id ID of projectile.
   * @param target Optional target of projectile.
   */
  ProjectileScript(size_t projectile_id, std::optional<ProjectileTarget> target);

  void Update(std::chrono::microseconds delta, entities::WorldEntities &entities) override;
  bool IsCompleted() const override;

 private:
  /** ID of projectile. */
  size_t projectile_id_;
  /** Optional target of projectile. */
  std::optional<ProjectileTarget> target_;
  /** True if script completed its execution and target was hit if it was presented. */
  bool is_completed_;

};

}
