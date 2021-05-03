#pragma once

#include "unit/BasicFirearmWeapon.h"
#include "headquarters_model/tech/Tech.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierMachineGun.h"

namespace unit::soldier::weapon::firearm {

using namespace headquarters_model::tech;

/** Soldier firearm machine gun. */
class SoldierFirearmMachineGun : public BasicFirearmWeapon, public ISoldierMachineGun {
 public:
  /**
   * Creates soldier firearm machine gun.
   * @param tech Current tech state.
   */
  explicit SoldierFirearmMachineGun(const Tech &tech);

};

}
