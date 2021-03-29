#include "SoldierFirearmPistol.h"

namespace unit::soldier::weapon::firearm {

SoldierFirearmPistol::SoldierFirearmPistol(const config::GameConfig &game_config)
    : BasicFirearmWeapon(0, game_config.soldier_firearm_pistol_max_ammo,
                         game_config.soldier_firearm_pistol_mass) {

}

}
