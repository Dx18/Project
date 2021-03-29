#pragma once

#include "../IDroneWeaponFactory.h"
#include "DroneFirearmMachineGun.h"

namespace unit::drone::weapon::firearm {

/** Factory which creates drone firearm weapons. */
class DroneFirearmWeaponFactory : public IDroneWeaponFactory {
 private:
  /** Const reference to game config. */
  const config::GameConfig &game_config_;

 public:
  /**
   * Creates drone firearm weapon factory.
   * @param game_config Game process config.
   */
  explicit DroneFirearmWeaponFactory(const config::GameConfig &game_config);

  [[nodiscard]] std::unique_ptr<unit::drone::weapon::IDroneMachineGun> CreateMachineGun() const override;

};

}
