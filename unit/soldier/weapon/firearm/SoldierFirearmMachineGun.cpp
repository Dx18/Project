#include "SoldierFirearmMachineGun.h"

namespace unit::soldier::weapon::firearm {

using namespace object_database;

SoldierFirearmMachineGun::SoldierFirearmMachineGun(const config::GameConfig &game_config)
    : BasicFirearmWeapon(0, game_config.WeaponMaxAmmo(WeaponType::kSoldierFirearmMachineGun).value(),
                         game_config.WeaponMass(WeaponType::kSoldierFirearmMachineGun)) {

}

}
