#include "SoldierLaserSniperRifle.h"

namespace unit::soldier::weapon::laser {

SoldierLaserSniperRifle::SoldierLaserSniperRifle(const config::GameConfig &game_config)
    : BasicLaserWeapon(game_config.soldier_laser_sniper_rifle_mass) {

}

}
