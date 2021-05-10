#include "SoldierLaserShotgun.h"

namespace unit::soldier::weapon::laser {

using namespace object_database;

SoldierLaserShotgun::SoldierLaserShotgun(const Tech &tech)
    : BasicLaserWeapon(tech.WeaponMass(WeaponType::kSoldierLaserShotgun),
                       tech.WeaponBaseDamage(WeaponType::kSoldierLaserShotgun)) {

}

}
