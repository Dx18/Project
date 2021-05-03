#include "SoldierLaserMachineGun.h"

namespace unit::soldier::weapon::laser {

using namespace object_database;

SoldierLaserMachineGun::SoldierLaserMachineGun(const Tech &tech)
    : BasicLaserWeapon(tech.WeaponMass(WeaponType::kSoldierLaserMachineGun)) {

}

}
