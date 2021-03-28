#include "DroneFirearmWeaponFactory.h"

namespace unit::drone::weapon::firearm {

std::unique_ptr<IDroneMachineGun> DroneFirearmWeaponFactory::CreateMachineGun() const {
  return std::make_unique<DroneFirearmMachineGun>();
}

}
