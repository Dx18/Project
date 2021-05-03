#pragma once

#include "unit/BasicLaserWeapon.h"
#include "headquarters_model/tech/Tech.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierSniperRifle.h"

namespace unit::soldier::weapon::laser {

using namespace headquarters_model::tech;

/** Soldier laser sniper rifle. */
class SoldierLaserSniperRifle : public BasicLaserWeapon, public ISoldierSniperRifle {
 public:
  /**
   * Creates soldier laser sniper rifle.
   * @param tech Current tech state.
   */
  explicit SoldierLaserSniperRifle(const Tech &tech);

};

}
