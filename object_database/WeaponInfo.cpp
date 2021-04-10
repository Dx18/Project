#include "WeaponInfo.h"

namespace object_database {

WeaponInfo::WeaponInfo(WeaponType _type, std::string _name, bool _has_max_ammo)
    : type(_type), name(std::move(_name)), has_max_ammo(_has_max_ammo) {

}

const WeaponInfo WeaponInfo::kSoldierFirearmPistol
    (WeaponType::kSoldierFirearmPistol,
     "soldier_firearm_pistol",
     true);
const WeaponInfo WeaponInfo::kSoldierFirearmShotgun
    (WeaponType::kSoldierFirearmShotgun,
     "soldier_firearm_shotgun",
     true);
const WeaponInfo WeaponInfo::kSoldierFirearmSniperRifle
    (WeaponType::kSoldierFirearmSniperRifle,
     "soldier_firearm_sniper_rifle",
     true);
const WeaponInfo WeaponInfo::kSoldierFirearmMachineGun
    (WeaponType::kSoldierFirearmMachineGun,
     "soldier_firearm_machine_gun",
     true);
const WeaponInfo WeaponInfo::kSoldierLaserPistol
    (WeaponType::kSoldierLaserPistol,
     "soldier_laser_pistol",
     false);
const WeaponInfo WeaponInfo::kSoldierLaserShotgun
    (WeaponType::kSoldierLaserShotgun,
     "soldier_laser_shotgun",
     false);
const WeaponInfo WeaponInfo::kSoldierLaserSniperRifle
    (WeaponType::kSoldierLaserSniperRifle,
     "soldier_laser_sniper_rifle",
     false);
const WeaponInfo WeaponInfo::kSoldierLaserMachineGun
    (WeaponType::kSoldierLaserMachineGun,
     "soldier_laser_machine_gun",
     false);
const WeaponInfo WeaponInfo::kDroneFirearmMachineGun
    (WeaponType::kDroneFirearmMachineGun,
     "drone_firearm_machine_gun",
     true);
const WeaponInfo WeaponInfo::kDroneLaserMachineGun
    (WeaponType::kDroneLaserMachineGun,
     "drone_laser_machine_gun",
     false);

}
