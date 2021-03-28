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

}
