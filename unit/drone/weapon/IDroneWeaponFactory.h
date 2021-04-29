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

}
