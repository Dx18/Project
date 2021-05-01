#pragma once

#include <vector>
#include <memory>

#include "IWorldScript.h"

namespace world::script {

/** Scripts executed sequentially. */
class ScriptSequence : IWorldScript {
 public:
  /** Creates script sequence. */
  explicit ScriptSequence(std::vector<std::unique_ptr<IWorldScript>> &&scripts);

  void Update(std::chrono::microseconds delta, world::entities::WorldEntities &entities) override;
  [[nodiscard]] bool IsCompleted() const override;

 private:
  /** Scripts to execute. */
  std::vector<std::unique_ptr<IWorldScript>> scripts_;
  /** Index of first script not yet executed or count of scripts in sequence if execution was finished. */
  size_t current_;

};

}
