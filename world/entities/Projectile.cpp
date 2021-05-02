#include "Projectile.h"

namespace world::entities {

Projectile::Projectile(const util::Vector3<double> &source, const util::Vector3<double> &destination, double speed)
    : source_(source), destination_(destination), speed_(speed), progress_(0.0) {

}

void Projectile::Update(std::chrono::microseconds delta) {
  double delta_x = destination_.x - source_.x;
  double delta_y = destination_.y - source_.y;
  double delta_z = destination_.z - source_.z;
  double distance = std::sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);

  double delta_progress = delta.count() / 1000000.0 * speed_ / distance;
  progress_ = util::math::clamp(progress_ + delta_progress, 0.0, 1.0);
}

bool Projectile::IsAlive() const {
  return progress_ < 1.0;
}

util::Vector3<double> Projectile::CurrentPosition() const {
  return {
      source_.x + (destination_.x - source_.x) * progress_,
      source_.y + (destination_.y - source_.y) * progress_,
      source_.z + (destination_.z - source_.z) * progress_
  };
}

}
