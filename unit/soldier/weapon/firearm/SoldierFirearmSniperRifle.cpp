#include "SoldierFirearmSniperRifle.h"

namespace unit::soldier::weapon::firearm {

SoldierFirearmSniperRifle::SoldierFirearmSniperRifle(const config::GameConfig &game_config)
    : BasicFirearmWeapon(0, game_config.soldier_firearm_sniper_rifle_max_ammo,
                         game_config.soldier_firearm_sniper_rifle_mass) {

}

}
