#pragma once

#include "unit/BasicLaserWeapon.h"
#include "headquarters_model/tech/Tech.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierShotgun.h"

namespace unit::soldier::weapon::laser {

using namespace headquarters_model::tech;

/** Soldier laser shotgun. */
class SoldierLaserShotgun : public BasicLaserWeapon, public ISoldierShotgun {
 public:
  /**
   * Creates soldier laser shotgun.
   * @param tech Current tech state.
   */
  explicit SoldierLaserShotgun(const Tech &tech);

};

}
