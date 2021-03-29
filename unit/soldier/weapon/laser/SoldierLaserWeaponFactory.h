#pragma once

#include "config/GameConfig.h"

#include "../ISoldierWeaponFactory.h"
#include "SoldierLaserMachineGun.h"
#include "SoldierLaserPistol.h"
#include "SoldierLaserShotgun.h"
#include "SoldierLaserSniperRifle.h"

namespace unit::soldier::weapon::laser {

/** Factory which creates soldier laser weapons. */
class SoldierLaserWeaponFactory : public ISoldierWeaponFactory {
 private:
  /** Const reference to game config. */
  const config::GameConfig &game_config_;

 public:
  /**
   * Creates soldier laser weapon factory.
   * @param game_config Game process config.
   */
  explicit SoldierLaserWeaponFactory(const config::GameConfig &game_config);

  [[nodiscard]] std::unique_ptr<ISoldierPistol> CreatePistol() const override;
  [[nodiscard]] std::unique_ptr<ISoldierShotgun> CreateShotgun() const override;
  [[nodiscard]] std::unique_ptr<ISoldierSniperRifle> CreateSniperRifle() const override;
  [[nodiscard]] std::unique_ptr<ISoldierMachineGun> CreateMachineGun() const override;

};

}
