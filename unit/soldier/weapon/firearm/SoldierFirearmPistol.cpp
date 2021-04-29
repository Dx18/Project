#include "SoldierFirearmPistol.h"

namespace unit::soldier::weapon::firearm {

using namespace object_database;

SoldierFirearmPistol::SoldierFirearmPistol(const config::GameConfig &game_config)
    : BasicFirearmWeapon(0, game_config.WeaponMaxAmmo(WeaponType::kSoldierFirearmPistol).value(),
                         game_config.WeaponMass(WeaponType::kSoldierFirearmPistol)) {

}

}
