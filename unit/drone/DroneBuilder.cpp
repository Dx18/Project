#include "DroneBuilder.h"

namespace unit::drone {

DroneBuilder &DroneBuilder::WithWeapon(std::unique_ptr<IDroneWeapon> weapon) {
  current_.SetWeapon(std::move(weapon));
  return *this;
}

DroneBuilder &DroneBuilder::WithArmor(std::unique_ptr<IDroneArmor> armor) {
  current_.SetArmor(std::move(armor));
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
