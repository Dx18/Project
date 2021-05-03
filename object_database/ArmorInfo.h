#pragma once

#include <string>
#include <array>

#include "ArmorType.h"
#include "ArmorTechType.h"
#include "UnitType.h"

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
  /** Drone composite armor. */
  static const ArmorInfo kDroneCompositeArmor;

  /** Type of armor. */
  const ArmorType type;
  /** Tech type of armor. */
  const ArmorTechType tech_type;
  /** Type of unit able to use armor of current type. */
  const UnitType unit_type;
  /** Name of armor type. */
  const std::string name;

 private:
  /**
   * Creates armor info.
   * @param _type Type of armor.
   * @param _tech_type Tech type of armor.
   * @param _unit_type Type of unit able to use armor of current type.
   * @param _name Name of armor type.
   */
  ArmorInfo(ArmorType _type, ArmorTechType _tech_type, UnitType _unit_type, std::string _name);

};

/** Array of all available armor info. `ArmorType` can be used as index of this array. */
extern const std::array<ArmorInfo, 4> kArmorInfo;

}
