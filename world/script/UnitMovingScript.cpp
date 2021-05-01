#include "UnitMovingScript.h"

namespace world::script {

UnitMovingScript::UnitMovingScript(size_t unit_id, std::vector<util::Vector3<double>> path, double speed)
    : unit_id_(unit_id), path_(std::move(path)), speed_(speed), current_edge_(0), edge_progress_(0.0) {
  if (path_.empty()) {
    throw std::runtime_error("given path is empty");
  }
}

void UnitMovingScript::Update(std::chrono::microseconds delta, world::entities::WorldEntities &entities) {
  if (IsCompleted()) {
    return;
  }

  while (!IsCompleted() && delta.count() > 0) {
    util::Vector3<double> point1 = path_[current_edge_];
    util::Vector3<double> point2 = path_[current_edge_ + 1];

    double edge_delta_x = point2.x - point1.x;
    double edge_delta_y = point2.y - point1.y;
    double edge_delta_z = point2.z - point1.z;

    double edge_length = std::sqrt(
        edge_delta_x * edge_delta_x + edge_delta_y * edge_delta_y + edge_delta_z * edge_delta_z
    );

    double delta_progress = delta.count() / 1000000.0 * speed_ / edge_length;

    if (edge_progress_ + delta_progress >= 1.0) {
      delta = std::chrono::microseconds(static_cast<long long>(
                                            delta.count() - delta.count() * (1.0 - edge_progress_) / delta_progress
                                        ));
      ++current_edge_;
      edge_progress_ = 0.0;
    } else {
      edge_progress_ += delta_progress;
      break;
    }
  }

  if (IsCompleted()) {
    entities.GetUnit(unit_id_).SetPosition(path_.back());
  } else {
    util::Vector3<double> point1 = path_[current_edge_];
    util::Vector3<double> point2 = path_[current_edge_ + 1];

    double delta_x = (point2.x - point1.x) * edge_progress_;
    double delta_y = (point2.y - point1.y) * edge_progress_;
    double delta_z = (point2.z - point1.z) * edge_progress_;

    entities.GetUnit(unit_id_).SetPosition({
                                               point1.x + delta_x, point1.y + delta_y, point1.z + delta_z,
                                           });
  }
}

bool UnitMovingScript::IsCompleted() const {
  return current_edge_ == path_.size() - 1;
}

}
