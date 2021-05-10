#pragma once

#include <cmath>

#include "util/Vector.h"

#include "IWorldScript.h"

namespace world::script {

/** Script which executes unit movement. */
class UnitMovingScript : public IWorldScript {
 public:
  /**
   * Creates unit moving script. Given path must be non-empty. If given path is empty then constructor throws
   * `std::runtime_error`.
   * @param unit_id ID of unit to move.
   * @param path Path of unit represented as array of points.
   * @param speed Speed of unit (tiles per second).
   */
  UnitMovingScript(size_t unit_id, std::vector<util::Vector3<double>> path, double speed);

  void Update(std::chrono::microseconds delta, entities::WorldEntities &entities) override;
  bool IsCompleted() const override;

 private:
  /** ID of unit to move. */
  size_t unit_id_;
  /** Path of unit represented as array of points. */
  std::vector<util::Vector3<double>> path_;
  /** Speed of unit. */
  double speed_;
  /**
   * Current edge: index of first vertex of edge. Current edge is equal to `path_.size() - 1` if and only if script
   * execution was finished.
   */
  size_t current_edge_;
  /** Current progress of edge moving in range [0.0; 1.0]. */
  double edge_progress_;

};

}
