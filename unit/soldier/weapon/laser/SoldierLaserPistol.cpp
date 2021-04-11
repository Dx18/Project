#include "SoldierLaserPistol.h"

namespace unit::soldier::weapon::laser {

using namespace object_database;

SoldierLaserPistol::SoldierLaserPistol(const Tech &tech)
    : BasicLaserWeapon(tech.WeaponMass(WeaponType::kSoldierLaserPistol)) {

}

}
