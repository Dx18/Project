#include "IDroneMachineGun.h"

namespace unit::drone::weapon {

DroneFirearmMachineGun::DroneFirearmMachineGun()
    : BasicFirearmWeapon(0, kMaxAmmo, kMass) {

}

DroneLaserMachineGun::DroneLaserMachineGun()
    : BasicLaserWeapon(kMass) {

}

}