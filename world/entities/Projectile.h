#pragma once

#include <chrono>

#include "util/Vector.h"
#include "util/Math.h"

namespace world::entities {

/** Projectile. */
class Projectile {
 public:
  /**
   * Creates projectile.
   * @param source First position of projectile.
   * @param destination Last position of projectile.
   * @param speed Speed of projectile.
   */
  Projectile(const util::Vector3<double> &source, const util::Vector3<double> &destination, double speed);

  /**
   * Updates projectile.
   * @param delta Time passed since last frame.
   */
  void Update(std::chrono::microseconds delta);
  /** Returns true if projectile is still alive. */
  [[nodiscard]] bool IsAlive() const;

  /** Returns current position of projectile. */
  [[nodiscard]] util::Vector3<double> CurrentPosition() const;

 private:
  /** First position of projectile. */
  util::Vector3<double> source_;
  /** Last position of projectile. */
  util::Vector3<double> destination_;
  /** Speed of projectile. */
  double speed_;
  /** Current progress: value in range [0.0; 1.0]. */
  double progress_;

};

}
