#include "ISoldierShotgun.h"

namespace unit::soldier::weapon {

SoldierFirearmShotgun::SoldierFirearmShotgun()
    : BasicFirearmWeapon(0, kMaxAmmo, kMass) {

}

SoldierLaserShotgun::SoldierLaserShotgun()
    : BasicLaserWeapon(kMass) {

}

}