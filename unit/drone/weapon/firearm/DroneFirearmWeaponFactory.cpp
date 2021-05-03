#include "DroneFirearmWeaponFactory.h"

namespace unit::drone::weapon::firearm {

DroneFirearmWeaponFactory::DroneFirearmWeaponFactory(const Tech &tech)
    : tech_(tech) {

}

std::unique_ptr<IDroneMachineGun> DroneFirearmWeaponFactory::CreateMachineGun() const {
  return std::make_unique<DroneFirearmMachineGun>(tech_);
}

}
