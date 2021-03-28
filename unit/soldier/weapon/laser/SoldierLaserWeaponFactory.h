#pragma once

#include "../ISoldierWeaponFactory.h"
#include "SoldierLaserMachineGun.h"
#include "SoldierLaserPistol.h"
#include "SoldierLaserShotgun.h"
#include "SoldierLaserSniperRifle.h"

namespace unit::soldier::weapon::laser {

/** Factory which creates soldier laser weapons. */
class SoldierLaserWeaponFactory : public ISoldierWeaponFactory {
 public:
  [[nodiscard]] std::unique_ptr<ISoldierPistol> CreatePistol() const override;
  [[nodiscard]] std::unique_ptr<ISoldierShotgun> CreateShotgun() const override;
  [[nodiscard]] std::unique_ptr<ISoldierSniperRifle> CreateSniperRifle() const override;
  [[nodiscard]] std::unique_ptr<ISoldierMachineGun> CreateMachineGun() const override;

};

}
