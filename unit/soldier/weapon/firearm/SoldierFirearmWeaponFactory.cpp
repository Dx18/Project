#include "SoldierFirearmWeaponFactory.h"

namespace unit::soldier::weapon::firearm {

SoldierFirearmWeaponFactory::SoldierFirearmWeaponFactory(const config::GameConfig &game_config)
    : game_config_(game_config) {

}

std::unique_ptr<ISoldierPistol> SoldierFirearmWeaponFactory::CreatePistol() const {
  return std::make_unique<SoldierFirearmPistol>(game_config_);
}

std::unique_ptr<ISoldierShotgun> SoldierFirearmWeaponFactory::CreateShotgun() const {
  return std::make_unique<SoldierFirearmShotgun>(game_config_);
}

std::unique_ptr<ISoldierSniperRifle> SoldierFirearmWeaponFactory::CreateSniperRifle() const {
  return std::make_unique<SoldierFirearmSniperRifle>(game_config_);
}

std::unique_ptr<ISoldierMachineGun> SoldierFirearmWeaponFactory::CreateMachineGun() const {
  return std::make_unique<SoldierFirearmMachineGun>(game_config_);
}

}
