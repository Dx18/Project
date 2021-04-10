#pragma once

namespace object_database {

/** Type of weapon. */
enum WeaponType {
  /** Soldier firearm pistol. */
  kSoldierFirearmPistol = 0,
  /** Soldier firearm shotgun. */
  kSoldierFirearmShotgun = 1,
  /** Soldier firearm sniper rifle. */
  kSoldierFirearmSniperRifle = 2,
  /** Soldier firearm machine gun. */
  kSoldierFirearmMachineGun = 3,
  /** Soldier laser pistol. */
  kSoldierLaserPistol = 4,
  /** Soldier laser shotgun. */
  kSoldierLaserShotgun = 5,
  /** Soldier laser sniper rifle. */
  kSoldierLaserSniperRifle = 6,
  /** Soldier laser machine gun. */
  kSoldierLaserMachineGun = 7,
  /** Drone firearm machine gun. */
  kDroneFirearmMachineGun = 8,
  /** Drone laser machine gun. */
  kDroneLaserMachineGun = 9
};

}
