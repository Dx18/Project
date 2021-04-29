#include "SoldierLaserPistol.h"

namespace unit::soldier::weapon::laser {

using namespace object_database;

SoldierLaserPistol::SoldierLaserPistol(const config::GameConfig &game_config)
    : BasicLaserWeapon(game_config.WeaponMass(WeaponType::kSoldierLaserPistol)) {

}

}
