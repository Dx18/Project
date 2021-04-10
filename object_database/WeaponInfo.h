#pragma once

#include <string>
#include <array>

#include "WeaponType.h"

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
  /** Name of weapon type. */
  const std::string name;
  /** True if weapon has max amount of ammo. */
  const bool has_max_ammo;

 private:
  /**
   * Creates weapon info.
   * @param _type Type of weapon.
   * @param _name Name of weapon type.
   * @param _has_max_ammo True if weapon has max amount of ammo.
   */
  WeaponInfo(WeaponType _type, std::string _name, bool _has_max_ammo);

};

/** Array of all available weapon info. `WeaponType` can be used as index of this array. */
static const std::array<WeaponInfo, 10> kWeaponInfo = {
    WeaponInfo::kSoldierFirearmPistol,
    WeaponInfo::kSoldierFirearmShotgun,
    WeaponInfo::kSoldierFirearmSniperRifle,
    WeaponInfo::kSoldierFirearmMachineGun,
    WeaponInfo::kSoldierLaserPistol,
    WeaponInfo::kSoldierLaserShotgun,
    WeaponInfo::kSoldierLaserSniperRifle,
    WeaponInfo::kSoldierLaserMachineGun,
    WeaponInfo::kDroneFirearmMachineGun,
    WeaponInfo::kDroneLaserMachineGun
};

}
