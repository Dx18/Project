#include "WeaponTechInfo.h"

namespace object_database {

WeaponTechInfo::WeaponTechInfo(WeaponTechType _tech_type, std::string _name)
    : tech_type(_tech_type), name(std::move(_name)) {

}

const WeaponTechInfo WeaponTechInfo::kFirearm
    (WeaponTechType::kFirearm,
     "firearm_weapon");
const WeaponTechInfo WeaponTechInfo::kLaser
    (WeaponTechType::kLaser,
     "laser_weapon");

const std::array<WeaponTechInfo, 2> kWeaponTechInfo = {
    WeaponTechInfo::kFirearm,
    WeaponTechInfo::kLaser
};

}
