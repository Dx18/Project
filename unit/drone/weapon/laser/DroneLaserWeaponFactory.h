#pragma once

#include "headquarters_model/tech/Tech.h"

#include "../IDroneWeaponFactory.h"
#include "DroneLaserMachineGun.h"

namespace unit::drone::weapon::laser {

using namespace headquarters_model::tech;

/** Factory which creates drone laser weapons. */
class DroneLaserWeaponFactory : public IDroneWeaponFactory {
 private:
  /** Const reference to headquarters tech. */
  const Tech &tech_;

 public:
  /**
   * Creates drone firearm weapon factory.
   * @param tech Current tech state.
   */
  explicit DroneLaserWeaponFactory(const Tech &tech);

  [[nodiscard]] std::unique_ptr<IDroneMachineGun> CreateMachineGun() const override;

};

}
