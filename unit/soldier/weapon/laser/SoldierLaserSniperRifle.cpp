#include "SoldierLaserSniperRifle.h"

namespace unit::soldier::weapon::laser {

using namespace object_database;

SoldierLaserSniperRifle::SoldierLaserSniperRifle(const config::GameConfig &game_config)
    : BasicLaserWeapon(game_config.WeaponMass(WeaponType::kSoldierLaserSniperRifle)) {

}

}
