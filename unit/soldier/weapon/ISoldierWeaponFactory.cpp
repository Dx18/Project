#include "ISoldierWeaponFactory.h"

namespace unit::soldier::weapon {

std::unique_ptr<ISoldierPistol> SoldierFirearmWeaponFactory::CreatePistol() const {
  return std::make_unique<SoldierFirearmPistol>();
}

std::unique_ptr<ISoldierShotgun> SoldierFirearmWeaponFactory::CreateShotgun() const {
  return std::make_unique<SoldierFirearmShotgun>();
}

std::unique_ptr<ISoldierSniperRifle> SoldierFirearmWeaponFactory::CreateSniperRifle() const {
  return std::make_unique<SoldierFirearmSniperRifle>();
}

std::unique_ptr<ISoldierMachineGun> SoldierFirearmWeaponFactory::CreateMachineGun() const {
  return std::make_unique<SoldierFirearmMachineGun>();
}

std::unique_ptr<ISoldierPistol> SoldierLaserWeaponFactory::CreatePistol() const {
  return std::make_unique<SoldierLaserPistol>();
}

std::unique_ptr<ISoldierShotgun> SoldierLaserWeaponFactory::CreateShotgun() const {
  return std::make_unique<SoldierLaserShotgun>();
}

std::unique_ptr<ISoldierSniperRifle> SoldierLaserWeaponFactory::CreateSniperRifle() const {
  return std::make_unique<SoldierLaserSniperRifle>();
}

std::unique_ptr<ISoldierMachineGun> SoldierLaserWeaponFactory::CreateMachineGun() const {
  return std::make_unique<SoldierLaserMachineGun>();
}


}