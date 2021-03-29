#include "SoldierFirearmShotgun.h"

namespace unit::soldier::weapon::firearm {

SoldierFirearmShotgun::SoldierFirearmShotgun(const config::GameConfig &game_config)
    : BasicFirearmWeapon(0, game_config.soldier_firearm_shotgun_max_ammo,
                         game_config.soldier_firearm_shotgun_mass) {

}

}
