#include "SoldierFirearmWeaponFactory.h"

namespace unit::soldier::weapon::firearm {

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

}
