#include "DroneLaserMachineGun.h"

namespace unit::drone::weapon::laser {

DroneLaserMachineGun::DroneLaserMachineGun(const config::GameConfig &game_config)
    : BasicLaserWeapon(game_config.drone_laser_machine_gun_mass) {

}

}
