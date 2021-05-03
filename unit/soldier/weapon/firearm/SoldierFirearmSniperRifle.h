#pragma once

#include "unit/BasicFirearmWeapon.h"
#include "headquarters_model/tech/Tech.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierSniperRifle.h"

namespace unit::soldier::weapon::firearm {

using namespace headquarters_model::tech;

/** Soldier firearm sniper rifle. */
class SoldierFirearmSniperRifle : public BasicFirearmWeapon, public ISoldierSniperRifle {
 public:
  /**
   * Creates soldier firearm sniper rifle.
   * @param tech Current tech state.
   */
  explicit SoldierFirearmSniperRifle(const Tech &tech);

};

}
