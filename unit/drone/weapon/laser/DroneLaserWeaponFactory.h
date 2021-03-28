#pragma once

#include "../IDroneWeaponFactory.h"
#include "DroneLaserMachineGun.h"

namespace unit::drone::weapon::laser {

/** Factory which creates drone laser weapons. */
class DroneLaserWeaponFactory : public IDroneWeaponFactory {
 public:
  [[nodiscard]] std::unique_ptr<IDroneMachineGun> CreateMachineGun() const override;

};

}
