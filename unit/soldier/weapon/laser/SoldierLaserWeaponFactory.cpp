#include "SoldierLaserWeaponFactory.h"

namespace unit::soldier::weapon::laser {

SoldierLaserWeaponFactory::SoldierLaserWeaponFactory(const Tech &tech)
    : tech_(tech) {

}

std::unique_ptr<ISoldierPistol> SoldierLaserWeaponFactory::CreatePistol() const {
  return std::make_unique<SoldierLaserPistol>(tech_);
}

std::unique_ptr<ISoldierShotgun> SoldierLaserWeaponFactory::CreateShotgun() const {
  return std::make_unique<SoldierLaserShotgun>(tech_);
}

std::unique_ptr<ISoldierSniperRifle> SoldierLaserWeaponFactory::CreateSniperRifle() const {
  return std::make_unique<SoldierLaserSniperRifle>(tech_);
}

std::unique_ptr<ISoldierMachineGun> SoldierLaserWeaponFactory::CreateMachineGun() const {
  return std::make_unique<SoldierLaserMachineGun>(tech_);
}

}
