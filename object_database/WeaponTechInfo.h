#pragma once

#include <string>

#include "WeaponTechType.h"

namespace object_database {

/** Information about weapon tech type. */
class WeaponTechInfo {
 public:
  /** Firearm weapon. */
  static const WeaponTechInfo kFirearm;
  /** Laser weapon. */
  static const WeaponTechInfo kLaser;

  /** Type of weapon tech type. */
  const WeaponTechType tech_type;
  /** Name of weapon tech type. */
  const std::string name;

 private:
  /**
   * Creates weapon tech type info.
   * @param _tech_type Tech type of weapon.
   * @param _name Name of weapon tech type.
   */
  WeaponTechInfo(WeaponTechType _tech_type, std::string _name);

};

/** Array of all available weapon tech info. `WeaponTechType` can be used as index of this array. */
extern const std::array<WeaponTechInfo, 2> kWeaponTechInfo;

}
