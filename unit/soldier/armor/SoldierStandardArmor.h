#pragma once

#include "unit/BasicArmor.h"

#include "ISoldierArmor.h"

namespace unit::soldier::armor {

/** Soldier standard armor. */
class SoldierStandardArmor : public BasicArmor, public ISoldierArmor {
 public:
  /** Default defence for soldier standard armor. */
  static const int kDefence = 4;
  /** Default mass for soldier standard armor. */
  static const int kMass = 5;

  SoldierStandardArmor();

};

}
