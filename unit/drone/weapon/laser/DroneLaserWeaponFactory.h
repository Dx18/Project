#pragma once

#include "../IDroneWeaponFactory.h"
#include "DroneLaserMachineGun.h"

namespace unit::drone::weapon::laser {

/** Factory which creates drone laser weapons. */
class DroneLaserWeaponFactory : public IDroneWeaponFactory {
 private:
  /** Const reference to game config. */
  const config::GameConfig &game_config_;

 public:
  /**
   * Creates drone firearm weapon factory.
   * @param game_config Game process config.
   */
  explicit DroneLaserWeaponFactory(const config::GameConfig &game_config);

  [[nodiscard]] std::unique_ptr<IDroneMachineGun> CreateMachineGun() const override;

};

}
