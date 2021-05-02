#include "SoldierFirearmPistol.h"

namespace unit::soldier::weapon::firearm {

using namespace object_database;

SoldierFirearmPistol::SoldierFirearmPistol(const Tech &tech)
    : BasicFirearmWeapon(0, tech.WeaponMaxAmmo(WeaponType::kSoldierFirearmPistol).value(),
                         tech.WeaponMass(WeaponType::kSoldierFirearmPistol),
                         tech.WeaponBaseDamage(WeaponType::kSoldierFirearmPistol)) {

}

}
