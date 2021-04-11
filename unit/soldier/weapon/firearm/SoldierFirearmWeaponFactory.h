#pragma once

#include "headquarters_model/tech/Tech.h"

#include "../ISoldierWeaponFactory.h"
#include "SoldierFirearmMachineGun.h"
#include "SoldierFirearmPistol.h"
#include "SoldierFirearmShotgun.h"
#include "SoldierFirearmSniperRifle.h"

namespace unit::soldier::weapon::firearm {

using namespace headquarters_model::tech;

/** Factory which creates soldier firearm weapons. */
class SoldierFirearmWeaponFactory : public ISoldierWeaponFactory {
 private:
  /** Const reference to headquarters tech. */
  const Tech &tech_;

 public:
  /**
   * Creates soldier firearm weapon factory.
   * @param tech Current tech state.
   */
  explicit SoldierFirearmWeaponFactory(const Tech &tech);

  [[nodiscard]] std::unique_ptr<ISoldierPistol> CreatePistol() const override;
  [[nodiscard]] std::unique_ptr<ISoldierShotgun> CreateShotgun() const override;
  [[nodiscard]] std::unique_ptr<ISoldierSniperRifle> CreateSniperRifle() const override;
  [[nodiscard]] std::unique_ptr<ISoldierMachineGun> CreateMachineGun() const override;

};

}
