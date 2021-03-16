#pragma once

#include "unit/IWeapon.h"

#include "ISoldierWeapon.h"

namespace unit::soldier::weapon {

/** Soldier machine gun common interface. */
class ISoldierMachineGun : public ISoldierWeapon {

};

/** Soldier firearm machine gun. */
class SoldierFirearmMachineGun : public BasicFirearmWeapon, public ISoldierMachineGun {
 public:
  /** Default max ammo for soldier firearm machine gun. */
  static const int kMaxAmmo = 5;
  /** Default mass for soldier firearm machine gun. */
  static const int kMass = 5;

  SoldierFirearmMachineGun();

};

/** Soldier laser machine gun. */
class SoldierLaserMachineGun : public BasicLaserWeapon, public ISoldierMachineGun {
 public:
  /** Default mass for soldier laser machine gun. */
  static const int kMass = 4;

  SoldierLaserMachineGun();

};

}
