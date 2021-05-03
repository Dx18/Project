#include "SoldierFirearmWeaponFactory.h"

namespace unit::soldier::weapon::firearm {

SoldierFirearmWeaponFactory::SoldierFirearmWeaponFactory(const Tech &tech)
    : tech_(tech) {

}

std::unique_ptr<ISoldierPistol> SoldierFirearmWeaponFactory::CreatePistol() const {
  return std::make_unique<SoldierFirearmPistol>(tech_);
}

std::unique_ptr<ISoldierShotgun> SoldierFirearmWeaponFactory::CreateShotgun() const {
  return std::make_unique<SoldierFirearmShotgun>(tech_);
}

std::unique_ptr<ISoldierSniperRifle> SoldierFirearmWeaponFactory::CreateSniperRifle() const {
  return std::make_unique<SoldierFirearmSniperRifle>(tech_);
}

std::unique_ptr<ISoldierMachineGun> SoldierFirearmWeaponFactory::CreateMachineGun() const {
  return std::make_unique<SoldierFirearmMachineGun>(tech_);
}

}
