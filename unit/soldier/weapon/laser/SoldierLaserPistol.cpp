#include "SoldierLaserPistol.h"

namespace unit::soldier::weapon::laser {

SoldierLaserPistol::SoldierLaserPistol(const config::GameConfig &game_config)
    : BasicLaserWeapon(game_config.soldier_laser_pistol_mass) {

}

}
