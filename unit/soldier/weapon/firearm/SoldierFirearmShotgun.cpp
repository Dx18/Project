#include "SoldierFirearmShotgun.h"

namespace unit::soldier::weapon::firearm {

using namespace object_database;

SoldierFirearmShotgun::SoldierFirearmShotgun(const config::GameConfig &game_config)
    : BasicFirearmWeapon(0, game_config.WeaponMaxAmmo(WeaponType::kSoldierFirearmShotgun).value(),
                         game_config.WeaponMass(WeaponType::kSoldierFirearmShotgun)) {

}

}
