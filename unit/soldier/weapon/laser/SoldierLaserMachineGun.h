#pragma once

#include "unit/BasicLaserWeapon.h"
#include "headquarters_model/tech/Tech.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierMachineGun.h"

namespace unit::soldier::weapon::laser {

using namespace headquarters_model::tech;

/** Soldier laser machine gun. */
class SoldierLaserMachineGun : public BasicLaserWeapon, public ISoldierMachineGun {
 public:
  /**
   * Creates soldier laser machine gun.
   * @param tech Current tech state.
   */
  explicit SoldierLaserMachineGun(const Tech &tech);

};

}
