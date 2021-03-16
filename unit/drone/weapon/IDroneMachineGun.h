#pragma once

#include "IDroneWeapon.h"

namespace unit::drone::weapon {

/** Drone machine gun common interface. */
class IDroneMachineGun : public IDroneWeapon {

};

/** Drone firearm machine gun. */
class DroneFirearmMachineGun : public BasicFirearmWeapon, public IDroneMachineGun {
 public:
  /** Default max ammo for drone firearm machine gun. */
  static const int kMaxAmmo = 5;
  /** Default mass for drone firearm machine gun. */
  static const int kMass = 4;

  DroneFirearmMachineGun();

};

/** Drone laser machine gun. */
class DroneLaserMachineGun : public BasicLaserWeapon, public IDroneMachineGun {
 public:
  /** Default mass for drone laser machine gun. */
  static const int kMass = 3;

  DroneLaserMachineGun();

};

}
