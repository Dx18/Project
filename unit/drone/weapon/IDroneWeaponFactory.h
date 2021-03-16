#pragma once

#include <memory>

#include "IDroneMachineGun.h"

namespace unit::drone::weapon {

/** Abstract factory which creates drone weapons. */
class IDroneWeaponFactory {
 public:
  /** Creates drone machine gun. */
  [[nodiscard]] virtual std::unique_ptr<IDroneMachineGun> CreateMachineGun() const = 0;

};

/** Factory which creates drone firearm weapons. */
class DroneFirearmWeaponFactory : public IDroneWeaponFactory {
 public:
  [[nodiscard]] std::unique_ptr<IDroneMachineGun> CreateMachineGun() const override;

};

/** Factory which creates drone laser weapons. */
class DroneLaserWeaponFactory : public IDroneWeaponFactory {
 public:
  [[nodiscard]] std::unique_ptr<IDroneMachineGun> CreateMachineGun() const override;

};

}
