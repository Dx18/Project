#pragma once

#include "unit/BasicArmor.h"

#include "IDroneArmor.h"

namespace unit::drone::armor {

/** Drone standard armor. */
class DroneStandardArmor : public BasicArmor, public IDroneArmor {
 public:
  /** Default defence for drone standard armor. */
  static const int kDefence = 3;
  /** Default mass for drone standard armor. */
  static const int kMass = 3;

  DroneStandardArmor();

};

}
