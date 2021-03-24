#include "ISoldierMachineGun.h"

namespace unit::soldier::weapon {

SoldierFirearmMachineGun::SoldierFirearmMachineGun()
    : BasicFirearmWeapon(0, kMaxAmmo, kMass) {

}

SoldierLaserMachineGun::SoldierLaserMachineGun()
    : BasicLaserWeapon(kMass) {

}

}
