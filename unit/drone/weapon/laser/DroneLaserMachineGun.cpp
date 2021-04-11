#include "DroneLaserMachineGun.h"

namespace unit::drone::weapon::laser {

using namespace object_database;

DroneLaserMachineGun::DroneLaserMachineGun(const config::GameConfig &game_config)
    : BasicLaserWeapon(game_config.WeaponMass(kDroneLaserMachineGun)) {

}

}
