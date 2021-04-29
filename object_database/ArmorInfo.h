#pragma once

#include <string>
#include <array>

#include "ArmorType.h"

namespace object_database {

/** Information about armor type. */
class ArmorInfo {
 public:
  /** Soldier standard armor. */
  static const ArmorInfo kSoldierStandardArmor;
  /** Soldier composite armor. */
  static const ArmorInfo kSoldierCompositeArmor;
  /** Drone standard armor. */
  static const ArmorInfo kDroneStandardArmor;

  /** Type of armor. */
  const ArmorType type;
  /** Name of armor type. */
  const std::string name;

 private:
  /**
   * Creates armor info.
   * @param _type Type of armor.
   * @param _name Name of armor type.
   */
  ArmorInfo(ArmorType _type, std::string _name);

};

/** Array of all available armor info. `ArmorType` can be used as index of this array. */
extern const std::array<ArmorInfo, 3> kArmorInfo;

}
