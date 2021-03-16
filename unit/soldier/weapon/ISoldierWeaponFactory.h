#pragma once

#include <memory>

#include "ISoldierPistol.h"
#include "ISoldierShotgun.h"
#include "ISoldierSniperRifle.h"
#include "ISoldierMachineGun.h"

namespace unit::soldier::weapon {

/** Abstract factory which creates soldier weapons. */
class ISoldierWeaponFactory {
 public:
  /** Creates soldier pistol. */
  [[nodiscard]] virtual std::unique_ptr<ISoldierPistol> CreatePistol() const = 0;
  /** Creates soldier shotgun. */
  [[nodiscard]] virtual std::unique_ptr<ISoldierShotgun> CreateShotgun() const = 0;
  /** Creates soldier sniper rifle. */
  [[nodiscard]] virtual std::unique_ptr<ISoldierSniperRifle> CreateSniperRifle() const = 0;
  /** Creates soldier machine gun. */
  [[nodiscard]] virtual std::unique_ptr<ISoldierMachineGun> CreateMachineGun() const = 0;

};

/** Factory which creates soldier firearm weapons. */
class SoldierFirearmWeaponFactory : public ISoldierWeaponFactory {
 public:
  [[nodiscard]] std::unique_ptr<ISoldierPistol> CreatePistol() const override;
  [[nodiscard]] std::unique_ptr<ISoldierShotgun> CreateShotgun() const override;
  [[nodiscard]] std::unique_ptr<ISoldierSniperRifle> CreateSniperRifle() const override;
  [[nodiscard]] std::unique_ptr<ISoldierMachineGun> CreateMachineGun() const override;

};

/** Factory which creates soldier laser weapons. */
class SoldierLaserWeaponFactory : public ISoldierWeaponFactory {
public:
 [[nodiscard]] std::unique_ptr<ISoldierPistol> CreatePistol() const override;
 [[nodiscard]] std::unique_ptr<ISoldierShotgun> CreateShotgun() const override;
 [[nodiscard]] std::unique_ptr<ISoldierSniperRifle> CreateSniperRifle() const override;
 [[nodiscard]] std::unique_ptr<ISoldierMachineGun> CreateMachineGun() const override;

};

}
