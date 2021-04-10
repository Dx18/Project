#include "SoldierFirearmSniperRifle.h"

namespace unit::soldier::weapon::firearm {

using namespace object_database;

SoldierFirearmSniperRifle::SoldierFirearmSniperRifle(const config::GameConfig &game_config)
    : BasicFirearmWeapon(0, game_config.WeaponMaxAmmo(WeaponType::kSoldierFirearmSniperRifle).value(),
                         game_config.WeaponMass(WeaponType::kSoldierFirearmSniperRifle)) {

}

}
