#pragma once

#include "unit/BasicArmor.h"
#include "headquarters_model/tech/Tech.h"

#include "ISoldierArmor.h"

namespace unit::soldier::armor {

using namespace headquarters_model::tech;

/** Soldier composite armor. */
class SoldierCompositeArmor : public BasicArmor, public ISoldierArmor {
 public:
  /**
   * Creates soldier composite armor.
   * @param tech Current tech state.
   */
  explicit SoldierCompositeArmor(const Tech &tech);

};

}
