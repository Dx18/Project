#pragma once

#include <string>

#include "ArmorTechType.h"

namespace object_database {

/** Information about armor tech type. */
class ArmorTechInfo {
 public:
  /** Standard armor. */
  static const ArmorTechInfo kStandard;
  /** Composite armor. */
  static const ArmorTechInfo kComposite;

  /** Type of armor tech type. */
  const ArmorTechType tech_type;
  /** Name of armor tech type. */
  const std::string name;

 private:
  /**
   * Creates armor tech type info.
   * @param _tech_type Tech type of armor.
   * @param _name Name of armor tech type.
   */
  ArmorTechInfo(ArmorTechType _tech_type, std::string _name);

};

/** Array of all available armor tech info. `ArmorTechType` can be used as index of this array. */
extern const std::array<ArmorTechInfo, 2> kArmorTechInfo;

}
