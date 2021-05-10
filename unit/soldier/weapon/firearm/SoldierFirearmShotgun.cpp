#include "SoldierFirearmShotgun.h"

namespace unit::soldier::weapon::firearm {

using namespace object_database;

SoldierFirearmShotgun::SoldierFirearmShotgun(const Tech &tech)
    : BasicFirearmWeapon(0, tech.WeaponMaxAmmo(WeaponType::kSoldierFirearmShotgun).value(),
                         tech.WeaponMass(WeaponType::kSoldierFirearmShotgun),
                         tech.WeaponBaseDamage(WeaponType::kSoldierFirearmShotgun)) {

}

}
