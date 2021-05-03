#pragma once

#include "headquarters_model/tech/Tech.h"

#include "../ISoldierWeaponFactory.h"
#include "SoldierLaserMachineGun.h"
#include "SoldierLaserPistol.h"
#include "SoldierLaserShotgun.h"
#include "SoldierLaserSniperRifle.h"

namespace unit::soldier::weapon::laser {

using namespace headquarters_model::tech;

/** Factory which creates soldier laser weapons. */
class SoldierLaserWeaponFactory : public ISoldierWeaponFactory {
 private:
  /** Const reference to headquarters tech. */
  const Tech &tech_;

 public:
  /**
   * Creates soldier laser weapon factory.
   * @param tech Current tech state.
   */
  explicit SoldierLaserWeaponFactory(const Tech &tech);

  [[nodiscard]] std::unique_ptr<ISoldierPistol> CreatePistol() const override;
  [[nodiscard]] std::unique_ptr<ISoldierShotgun> CreateShotgun() const override;
  [[nodiscard]] std::unique_ptr<ISoldierSniperRifle> CreateSniperRifle() const override;
  [[nodiscard]] std::unique_ptr<ISoldierMachineGun> CreateMachineGun() const override;

};

}
