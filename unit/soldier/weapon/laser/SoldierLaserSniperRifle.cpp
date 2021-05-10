#include "SoldierLaserSniperRifle.h"

namespace unit::soldier::weapon::laser {

using namespace object_database;

SoldierLaserSniperRifle::SoldierLaserSniperRifle(const Tech &tech)
    : BasicLaserWeapon(tech.WeaponMass(WeaponType::kSoldierLaserSniperRifle),
                       tech.WeaponBaseDamage(WeaponType::kSoldierLaserSniperRifle)) {

}

}
