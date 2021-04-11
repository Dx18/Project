#pragma once

#include "unit/BasicFirearmWeapon.h"
#include "headquarters_model/tech/Tech.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierShotgun.h"

namespace unit::soldier::weapon::firearm {

using namespace headquarters_model::tech;

/** Soldier firearm shotgun. */
class SoldierFirearmShotgun : public BasicFirearmWeapon, public ISoldierShotgun {
 public:
  /**
   * Creates soldier firearm shotgun.
   * @param tech Current tech state.
   */
  explicit SoldierFirearmShotgun(const Tech &tech);

};

}
