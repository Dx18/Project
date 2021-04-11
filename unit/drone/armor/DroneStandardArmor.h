#pragma once

#include "unit/BasicArmor.h"
#include "headquarters_model/tech/Tech.h"

#include "IDroneArmor.h"

namespace unit::drone::armor {

using namespace headquarters_model::tech;

/** Drone standard armor. */
class DroneStandardArmor : public BasicArmor, public IDroneArmor {
 public:
  /**
   * Creates drone standard armor.
   * @param tech Current tech state.
   */
  explicit DroneStandardArmor(const Tech &tech);

};

}
