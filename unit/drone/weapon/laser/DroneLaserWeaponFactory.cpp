#include "DroneLaserWeaponFactory.h"

namespace unit::drone::weapon::laser {

DroneLaserWeaponFactory::DroneLaserWeaponFactory(const config::GameConfig &game_config)
    : game_config_(game_config) {

}

std::unique_ptr<IDroneMachineGun> DroneLaserWeaponFactory::CreateMachineGun() const {
  return std::make_unique<DroneLaserMachineGun>(game_config_);
}

}
