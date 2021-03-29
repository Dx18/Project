#include "SoldierLaserWeaponFactory.h"

namespace unit::soldier::weapon::laser {

SoldierLaserWeaponFactory::SoldierLaserWeaponFactory(const config::GameConfig &game_config)
    : game_config_(game_config) {

}

std::unique_ptr<ISoldierPistol> SoldierLaserWeaponFactory::CreatePistol() const {
  return std::make_unique<SoldierLaserPistol>(game_config_);
}

std::unique_ptr<ISoldierShotgun> SoldierLaserWeaponFactory::CreateShotgun() const {
  return std::make_unique<SoldierLaserShotgun>(game_config_);
}

std::unique_ptr<ISoldierSniperRifle> SoldierLaserWeaponFactory::CreateSniperRifle() const {
  return std::make_unique<SoldierLaserSniperRifle>(game_config_);
}

std::unique_ptr<ISoldierMachineGun> SoldierLaserWeaponFactory::CreateMachineGun() const {
  return std::make_unique<SoldierLaserMachineGun>(game_config_);
}

}
