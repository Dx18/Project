#include "DroneLaserWeaponFactory.h"

namespace unit::drone::weapon::laser {

DroneLaserWeaponFactory::DroneLaserWeaponFactory(const Tech &tech)
    : tech_(tech) {

}

std::unique_ptr<IDroneMachineGun> DroneLaserWeaponFactory::CreateMachineGun() const {
  return std::make_unique<DroneLaserMachineGun>(tech_);
}

}
