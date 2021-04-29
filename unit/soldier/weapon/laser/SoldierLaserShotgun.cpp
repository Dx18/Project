#include "SoldierLaserShotgun.h"

namespace unit::soldier::weapon::laser {

using namespace object_database;

SoldierLaserShotgun::SoldierLaserShotgun(const config::GameConfig &game_config)
    : BasicLaserWeapon(game_config.WeaponMass(WeaponType::kSoldierLaserShotgun)) {

}

}
