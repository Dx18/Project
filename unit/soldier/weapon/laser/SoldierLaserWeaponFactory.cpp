#include "SoldierLaserWeaponFactory.h"

namespace unit::soldier::weapon::laser {

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
