#include "WeaponInfo.h"

namespace object_database {

WeaponInfo::WeaponInfo(WeaponType _type, WeaponTechType _tech_type, WeaponClassType _class_type, UnitType _unit_type,
                       std::string _name, bool _has_max_ammo)
    : type(_type), tech_type(_tech_type), class_type(_class_type), unit_type(_unit_type), name(std::move(_name)),
      has_max_ammo(_has_max_ammo) {

}

const WeaponInfo WeaponInfo::kSoldierFirearmPistol
    (WeaponType::kSoldierFirearmPistol,
     WeaponTechType::kFirearm,
     WeaponClassType::kPistol,
     UnitType::kSoldier,
     "soldier_firearm_pistol",
     true);
const WeaponInfo WeaponInfo::kSoldierFirearmShotgun
    (WeaponType::kSoldierFirearmShotgun,
     WeaponTechType::kFirearm,
     WeaponClassType::kShotgun,
     UnitType::kSoldier,
     "soldier_firearm_shotgun",
     true);
const WeaponInfo WeaponInfo::kSoldierFirearmSniperRifle
    (WeaponType::kSoldierFirearmSniperRifle,
     WeaponTechType::kFirearm,
     WeaponClassType::kSniperRifle,
     UnitType::kSoldier,
     "soldier_firearm_sniper_rifle",
     true);
const WeaponInfo WeaponInfo::kSoldierFirearmMachineGun
    (WeaponType::kSoldierFirearmMachineGun,
     WeaponTechType::kFirearm,
     WeaponClassType::kMachineGun,
     UnitType::kSoldier,
     "soldier_firearm_machine_gun",
     true);
const WeaponInfo WeaponInfo::kSoldierLaserPistol
    (WeaponType::kSoldierLaserPistol,
     WeaponTechType::kLaser,
     WeaponClassType::kPistol,
     UnitType::kSoldier,
     "soldier_laser_pistol",
     false);
const WeaponInfo WeaponInfo::kSoldierLaserShotgun
    (WeaponType::kSoldierLaserShotgun,
     WeaponTechType::kLaser,
     WeaponClassType::kShotgun,
     UnitType::kSoldier,
     "soldier_laser_shotgun",
     false);
const WeaponInfo WeaponInfo::kSoldierLaserSniperRifle
    (WeaponType::kSoldierLaserSniperRifle,
     WeaponTechType::kLaser,
     WeaponClassType::kSniperRifle,
     UnitType::kSoldier,
     "soldier_laser_sniper_rifle",
     false);
const WeaponInfo WeaponInfo::kSoldierLaserMachineGun
    (WeaponType::kSoldierLaserMachineGun,
     WeaponTechType::kLaser,
     WeaponClassType::kMachineGun,
     UnitType::kSoldier,
     "soldier_laser_machine_gun",
     false);
const WeaponInfo WeaponInfo::kDroneFirearmMachineGun
    (WeaponType::kDroneFirearmMachineGun,
     WeaponTechType::kFirearm,
     WeaponClassType::kMachineGun,
     UnitType::kDrone,
     "drone_firearm_machine_gun",
     true);
const WeaponInfo WeaponInfo::kDroneLaserMachineGun
    (WeaponType::kDroneLaserMachineGun,
     WeaponTechType::kLaser,
     WeaponClassType::kMachineGun,
     UnitType::kDrone,
     "drone_laser_machine_gun",
     false);

const std::array<WeaponInfo, 10> kWeaponInfo = {
    WeaponInfo::kSoldierFirearmPistol,
    WeaponInfo::kSoldierFirearmShotgun,
    WeaponInfo::kSoldierFirearmSniperRifle,
    WeaponInfo::kSoldierFirearmMachineGun,
    WeaponInfo::kSoldierLaserPistol,
    WeaponInfo::kSoldierLaserShotgun,
    WeaponInfo::kSoldierLaserSniperRifle,
    WeaponInfo::kSoldierLaserMachineGun,
    WeaponInfo::kDroneFirearmMachineGun,
    WeaponInfo::kDroneLaserMachineGun
};

}
