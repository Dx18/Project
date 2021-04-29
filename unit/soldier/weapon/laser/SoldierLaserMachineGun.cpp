#include "SoldierLaserMachineGun.h"

namespace unit::soldier::weapon::laser {

using namespace object_database;

SoldierLaserMachineGun::SoldierLaserMachineGun(const config::GameConfig &game_config)
    : BasicLaserWeapon(game_config.WeaponMass(WeaponType::kSoldierLaserMachineGun)) {

}

}
