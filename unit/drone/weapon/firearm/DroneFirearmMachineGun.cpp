#include "DroneFirearmMachineGun.h"

namespace unit::drone::weapon::firearm {

DroneFirearmMachineGun::DroneFirearmMachineGun(const config::GameConfig &game_config)
    : BasicFirearmWeapon(0, game_config.drone_firearm_machine_gun_max_ammo,
                         game_config.drone_firearm_machine_gun_mass) {

}

}
