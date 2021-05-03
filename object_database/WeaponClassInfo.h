#pragma once

#include <string>
#include <array>

#include "WeaponClassType.h"
#include "UnitType.h"

namespace object_database {

/** Information about weapon class type. */
class WeaponClassInfo {
 public:
  /** Pistol. */
  static const WeaponClassInfo kPistol;
  /** Shotgun. */
  static const WeaponClassInfo kShotgun;
  /** Sniper rifle. */
  static const WeaponClassInfo kSniperRifle;
  /** Machine gun. */
  static const WeaponClassInfo kMachineGun;

  /** Type of weapon class type. */
  const WeaponClassType type;
  /** Name of weapon class type. */
  const std::string name;

 private:
  /**
   * Creates weapon class type info.
   * @param _type Type of weapon class type.
   * @param _name Name of weapon class type.
   */
  WeaponClassInfo(WeaponClassType _type, std::string _name);

};

/** Array of all available weapon class info. `WeaponClassType` can be used as index of this array. */
extern const std::array<WeaponClassInfo, 4> kWeaponClassInfo;

}
