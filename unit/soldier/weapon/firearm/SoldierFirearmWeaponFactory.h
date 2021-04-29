#pragma once

#include "config/GameConfig.h"

#include "../ISoldierWeaponFactory.h"
#include "SoldierFirearmMachineGun.h"
#include "SoldierFirearmPistol.h"
#include "SoldierFirearmShotgun.h"
#include "SoldierFirearmSniperRifle.h"

namespace unit::soldier::weapon::firearm {

/** Factory which creates soldier firearm weapons. */
class SoldierFirearmWeaponFactory : public ISoldierWeaponFactory {
 private:
  /** Const reference to game config. */
  const config::GameConfig &game_config_;

 public:
  /**
   * Creates soldier firearm weapon factory.
   * @param game_config Game process config.
   */
  explicit SoldierFirearmWeaponFactory(const config::GameConfig &game_config);

  [[nodiscard]] std::unique_ptr<ISoldierPistol> CreatePistol() const override;
  [[nodiscard]] std::unique_ptr<ISoldierShotgun> CreateShotgun() const override;
  [[nodiscard]] std::unique_ptr<ISoldierSniperRifle> CreateSniperRifle() const override;
  [[nodiscard]] std::unique_ptr<ISoldierMachineGun> CreateMachineGun() const override;

};

}
