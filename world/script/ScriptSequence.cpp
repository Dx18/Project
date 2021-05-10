#include "ScriptSequence.h"

namespace world::script {

ScriptSequence::ScriptSequence(std::vector<std::unique_ptr<IWorldScript>> &&scripts)
    : scripts_(std::move(scripts)), current_(0) {

}

void ScriptSequence::Update(std::chrono::microseconds delta, world::entities::WorldEntities &entities) {
  while (current_ < scripts_.size() && scripts_[current_]->IsCompleted()) {
    ++current_;
  }

  if (current_ == scripts_.size()) {
    return;
  }

  scripts_[current_]->Update(delta, entities);
}

bool ScriptSequence::IsCompleted() const {
  return current_ == scripts_.size();
}

}
