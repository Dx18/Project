#pragma once

#include <string>
#include <array>

#include "WeaponType.h"
#include "WeaponTechType.h"
#include "WeaponClassType.h"
#include "UnitType.h"

namespace object_database {

/** Information about weapon type. */
class WeaponInfo {
 public:
  /** Soldier firearm pistol. */
  static const WeaponInfo kSoldierFirearmPistol;
  /** Soldier firearm shotgun. */
  static const WeaponInfo kSoldierFirearmShotgun;
  /** Soldier firearm sniper rifle. */
  static const WeaponInfo kSoldierFirearmSniperRifle;
  /** Soldier firearm machine gun. */
  static const WeaponInfo kSoldierFirearmMachineGun;
  /** Soldier laser pistol. */
  static const WeaponInfo kSoldierLaserPistol;
  /** Soldier laser shotgun. */
  static const WeaponInfo kSoldierLaserShotgun;
  /** Soldier laser sniper rifle. */
  static const WeaponInfo kSoldierLaserSniperRifle;
  /** Soldier laser machine gun. */
  static const WeaponInfo kSoldierLaserMachineGun;
  /** Drone firearm machine gun. */
  static const WeaponInfo kDroneFirearmMachineGun;
  /** Drone laser machine gun. */
  static const WeaponInfo kDroneLaserMachineGun;

  /** Type of weapon. */
  const WeaponType type;
  /** Tech type of weapon. */
  const WeaponTechType tech_type;
  /** Class type of weapon. */
  const WeaponClassType class_type;
  /** Type of unit able to use weapons of current type. */
  const UnitType unit_type;
  /** Name of weapon type. */
  const std::string name;
  /** True if weapon has max amount of ammo. */
  const bool has_max_ammo;

 private:
  /**
   * Creates weapon info.
   * @param _type Type of weapon.
   * @param _tech_type Tech type of weapon.
   * @param _class_type Class type of weapon.
   * @param _unit_type Type of unit able to use weapons of current type.
   * @param _name Name of weapon type.
   * @param _has_max_ammo True if weapon has max amount of ammo.
   */
  WeaponInfo(WeaponType _type, WeaponTechType _tech_type, WeaponClassType _class_type, UnitType _unit_type,
             std::string _name, bool _has_max_ammo);

};

/** Array of all available weapon info. `WeaponType` can be used as index of this array. */
extern const std::array<WeaponInfo, 10> kWeaponInfo;

}
