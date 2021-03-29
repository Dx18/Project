#include "SoldierLaserMachineGun.h"

namespace unit::soldier::weapon::laser {

SoldierLaserMachineGun::SoldierLaserMachineGun(const config::GameConfig &game_config)
    : BasicLaserWeapon(game_config.soldier_laser_machine_gun_mass) {

}

}
