#pragma once

#include "unit/BasicLaserWeapon.h"
#include "headquarters_model/tech/Tech.h"

#include "../ISoldierWeapon.h"
#include "../ISoldierPistol.h"

namespace unit::soldier::weapon::laser {

using namespace headquarters_model::tech;

/** Soldier laser pistol. */
class SoldierLaserPistol : public BasicLaserWeapon, public ISoldierPistol {
 public:
  /**
   * Creates soldier laser pistol.
   * @param tech Current tech state.
   */
  explicit SoldierLaserPistol(const Tech &tech);

};

}
