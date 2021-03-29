#include "SoldierFirearmMachineGun.h"

namespace unit::soldier::weapon::firearm {

SoldierFirearmMachineGun::SoldierFirearmMachineGun(const config::GameConfig &game_config)
    : BasicFirearmWeapon(0, game_config.soldier_firearm_machine_gun_max_ammo,
                         game_config.soldier_firearm_machine_gun_mass) {

}

}
