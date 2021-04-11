#include "DroneFirearmMachineGun.h"

namespace unit::drone::weapon::firearm {

using namespace object_database;

DroneFirearmMachineGun::DroneFirearmMachineGun(const Tech &tech)
    : BasicFirearmWeapon(0, tech.WeaponMaxAmmo(WeaponType::kDroneFirearmMachineGun).value(),
                         tech.WeaponMass(WeaponType::kDroneFirearmMachineGun)) {

}

}
