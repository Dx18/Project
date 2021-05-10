#include "SoldierFirearmSniperRifle.h"

namespace unit::soldier::weapon::firearm {

using namespace object_database;

SoldierFirearmSniperRifle::SoldierFirearmSniperRifle(const Tech &tech)
    : BasicFirearmWeapon(0, tech.WeaponMaxAmmo(WeaponType::kSoldierFirearmSniperRifle).value(),
                         tech.WeaponMass(WeaponType::kSoldierFirearmSniperRifle),
                         tech.WeaponBaseDamage(WeaponType::kSoldierFirearmSniperRifle)) {

}

}
