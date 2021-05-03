#pragma once

#include "unit/BasicArmor.h"
#include "headquarters_model/tech/Tech.h"

#include "../ISoldierArmor.h"

namespace unit::soldier::armor::standard {

using namespace headquarters_model::tech;

/** Soldier standard armor. */
class SoldierStandardArmor : public BasicArmor, public ISoldierArmor {
 public:
  /**
   * Creates soldier standard armor.
   * @param tech Current tech state.
   */
  explicit SoldierStandardArmor(const Tech &tech);

};

}
