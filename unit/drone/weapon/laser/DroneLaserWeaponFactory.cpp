#include "DroneLaserWeaponFactory.h"

namespace unit::drone::weapon::laser {

std::unique_ptr<IDroneMachineGun> DroneLaserWeaponFactory::CreateMachineGun() const {
  return std::make_unique<DroneLaserMachineGun>();
}

}
