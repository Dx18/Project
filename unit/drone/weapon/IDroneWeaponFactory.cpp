#include "IDroneWeaponFactory.h"

namespace unit::drone::weapon {

std::unique_ptr<IDroneMachineGun> DroneFirearmWeaponFactory::CreateMachineGun() const {
  return std::make_unique<DroneFirearmMachineGun>();
}

std::unique_ptr<IDroneMachineGun> DroneLaserWeaponFactory::CreateMachineGun() const {
  return std::make_unique<DroneLaserMachineGun>();
}

}