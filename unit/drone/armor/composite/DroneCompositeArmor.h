#pragma once

#include "unit/BasicArmor.h"
#include "headquarters_model/tech/Tech.h"

#include "unit/drone/armor/IDroneArmor.h"

namespace unit::drone::armor::composite {

using namespace headquarters_model::tech;

/** Drone composite armor. */
class DroneCompositeArmor : public BasicArmor, public IDroneArmor {
 public:
  /**
   * Creates drone composite armor.
   * @param tech Current tech state.
   */
  explicit DroneCompositeArmor(const Tech &tech);

};

}
