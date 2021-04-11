#include "DroneLaserMachineGun.h"

namespace unit::drone::weapon::laser {

using namespace object_database;

DroneLaserMachineGun::DroneLaserMachineGun(const Tech &tech)
    : BasicLaserWeapon(tech.WeaponMass(WeaponType::kDroneLaserMachineGun)) {

}

}
