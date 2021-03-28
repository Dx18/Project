#pragma once

#include "../IDroneWeaponFactory.h"
#include "DroneFirearmMachineGun.h"

namespace unit::drone::weapon::firearm {

/** Factory which creates drone firearm weapons. */
class DroneFirearmWeaponFactory : public IDroneWeaponFactory {
 public:
  [[nodiscard]] std::unique_ptr<unit::drone::weapon::IDroneMachineGun> CreateMachineGun() const override;

};

}
