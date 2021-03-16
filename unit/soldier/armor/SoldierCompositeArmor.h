#pragma once

#include "unit/IArmor.h"

#include "ISoldierArmor.h"

namespace unit::soldier::armor {

/** Soldier composite armor. */
class SoldierCompositeArmor : public BasicArmor, public ISoldierArmor {
 public:
  /** Default defence for soldier composite armor. */
  static const int kDefence = 8;
  /** Default mass for soldier composite armor. */
  static const int kMass = 6;

  SoldierCompositeArmor();

};

}
