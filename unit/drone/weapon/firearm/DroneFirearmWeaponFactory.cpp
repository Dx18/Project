#include "DroneFirearmWeaponFactory.h"

namespace unit::drone::weapon::firearm {

DroneFirearmWeaponFactory::DroneFirearmWeaponFactory(const config::GameConfig &game_config)
    : game_config_(game_config) {

}

std::unique_ptr<IDroneMachineGun> DroneFirearmWeaponFactory::CreateMachineGun() const {
  return std::make_unique<DroneFirearmMachineGun>(game_config_);
}

}
