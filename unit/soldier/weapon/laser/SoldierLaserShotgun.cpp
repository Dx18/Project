#include "SoldierLaserShotgun.h"

namespace unit::soldier::weapon::laser {

SoldierLaserShotgun::SoldierLaserShotgun(const config::GameConfig &game_config)
    : BasicLaserWeapon(game_config.soldier_laser_shotgun_mass) {

}

}
