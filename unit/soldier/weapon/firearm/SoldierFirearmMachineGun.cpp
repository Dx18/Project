#include "SoldierFirearmMachineGun.h"

namespace unit::soldier::weapon::firearm {

using namespace object_database;

SoldierFirearmMachineGun::SoldierFirearmMachineGun(const Tech &tech)
    : BasicFirearmWeapon(0, tech.WeaponMaxAmmo(WeaponType::kSoldierFirearmMachineGun).value(),
                         tech.WeaponMass(WeaponType::kSoldierFirearmMachineGun)) {

}

}
