#pragma once

#include <string>
#include <array>

#include "UnitType.h"

namespace object_database {

/** Information about unit type. */
class UnitInfo {
 public:
  /** Soldier. */
  static const UnitInfo kSoldier;
  /** Drone. */
  static const UnitInfo kDrone;

  /** Type of unit. */
  const UnitType type;
  /** Name of unit type. */
  const std::string name;

 private:
  /**
   * Creates unit info.
   * @param _type Type of unit.
   * @param _name Name of unit type.
   */
  UnitInfo(UnitType _type, std::string _name);

};

/** Array of all available unit info. `UnitType` can be used as index of this array. */
extern const std::array<UnitInfo, 2> kUnitInfo;

}
