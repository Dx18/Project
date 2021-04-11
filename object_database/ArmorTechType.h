#pragma once

#include <array>

namespace object_database {

/** Tech type of armor. */
enum ArmorTechType {
  /** Standard armor. */
  kStandard = 0,
  /** Composite armor. */
  kComposite = 1
};

/** Array of available armor tech types. */
extern const std::array<ArmorTechType, 2> kArmorTechTypes;

}
