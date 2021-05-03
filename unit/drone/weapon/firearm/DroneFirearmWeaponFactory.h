#pragma once

#include "headquarters_model/tech/Tech.h"

#include "../IDroneWeaponFactory.h"
#include "DroneFirearmMachineGun.h"

namespace unit::drone::weapon::firearm {

using namespace headquarters_model::tech;

/** Factory which creates drone firearm weapons. */
class DroneFirearmWeaponFactory : public IDroneWeaponFactory {
 private:
  /** Const reference to headquarters tech. */
  const Tech &tech_;

 public:
  /**
   * Creates drone firearm weapon factory.
   * @param tech Current tech state.
   */
  explicit DroneFirearmWeaponFactory(const Tech &tech);

  [[nodiscard]] std::unique_ptr<unit::drone::weapon::IDroneMachineGun> CreateMachineGun() const override;

};

}
