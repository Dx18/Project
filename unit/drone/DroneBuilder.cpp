#include "DroneBuilder.h"

namespace unit::drone {

DroneBuilder &DroneBuilder::WithWeapon(std::unique_ptr<IDroneWeapon> weapon) {
  current_.SetWeapon(std::move(weapon));
  return *this;
}

Drone DroneBuilder::Build() {
  Drone result;
  std::swap(result, current_);
  return result;
}

Unit &DroneBuilder::CurrentUnit() {
  return current_;
}

}
