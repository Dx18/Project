#include "ISoldierPistol.h"

namespace unit::soldier::weapon {

SoldierFirearmPistol::SoldierFirearmPistol()
    : BasicFirearmWeapon(0, kMaxAmmo, kMass) {

}

SoldierLaserPistol::SoldierLaserPistol()
    : BasicLaserWeapon(kMass) {

}

}