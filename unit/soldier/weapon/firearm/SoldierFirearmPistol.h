#pragma once

#include "unit/BasicFirearmWeapon.h"
#include "headquarters_model/tech/Tech.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierPistol.h"

namespace unit::soldier::weapon::firearm {

using namespace headquarters_model::tech;

/** Soldier firearm pistol. */
class SoldierFirearmPistol : public BasicFirearmWeapon, public ISoldierPistol {
 public:
  /**
   * Creates soldier firearm pistol.
   * @param tech Current tech state.
   */
  explicit SoldierFirearmPistol(const Tech &tech);

};

}
