#include "ISoldierSniperRifle.h"

namespace unit::soldier::weapon {

SoldierFirearmSniperRifle::SoldierFirearmSniperRifle()
    : BasicFirearmWeapon(0, kMaxAmmo, kMass) {

}

SoldierLaserSniperRifle::SoldierLaserSniperRifle()
    : BasicLaserWeapon(kMass) {

}

}