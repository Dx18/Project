#pragma once

#include <array>

namespace object_database {

/** Tech type of weapon. */
enum WeaponTechType {
  /** Firearm weapon. */
  kFirearm = 0,
  /** Laser weapon. */
  kLaser = 1
};

/** Array of available weapon tech types. */
extern const std::array<WeaponTechType, 2> kWeaponTechTypes;

}
