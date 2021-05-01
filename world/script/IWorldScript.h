#pragma once

#include <chrono>

#include "world/entities/WorldEntities.h"

namespace world::script {

/** Script executed in game world. */
class IWorldScript {
 public:
  /** Virtual destructor. */
  virtual ~IWorldScript() = 0;

  /**
   * Updates script. Does nothing if completed.
   * @param delta Time passed since last frame.
   * @param entities World entities.
   */
  virtual void Update(std::chrono::microseconds delta, world::entities::WorldEntities &entities) = 0;
  /** Returns true if script completed its execution. */
  [[nodiscard]] virtual bool IsCompleted() const = 0;

};

}
