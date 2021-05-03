#include "WeaponClassInfo.h"

namespace object_database {

WeaponClassInfo::WeaponClassInfo(WeaponClassType _type, std::string _name)
    : type(_type), name(std::move(_name)) {

}

const WeaponClassInfo WeaponClassInfo::kPistol
    (WeaponClassType::kPistol,
     "pistol");
const WeaponClassInfo WeaponClassInfo::kShotgun
    (WeaponClassType::kShotgun,
     "shotgun");
const WeaponClassInfo WeaponClassInfo::kSniperRifle
    (WeaponClassType::kSniperRifle,
     "sniper_rifle");
const WeaponClassInfo WeaponClassInfo::kMachineGun
    (WeaponClassType::kMachineGun,
     "machine_gun");

const std::array<WeaponClassInfo, 4> kWeaponClassInfo = {
    WeaponClassInfo::kPistol,
    WeaponClassInfo::kShotgun,
    WeaponClassInfo::kSniperRifle,
    WeaponClassInfo::kMachineGun
};

}
