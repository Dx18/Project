#include "DroneFirearmMachineGun.h"

namespace unit::drone::weapon::firearm {

using namespace object_database;

DroneFirearmMachineGun::DroneFirearmMachineGun(const config::GameConfig &game_config)
    : BasicFirearmWeapon(0, game_config.WeaponMaxAmmo(kDroneFirearmMachineGun).value(),
                         game_config.WeaponMass(kDroneFirearmMachineGun)) {

}

}
