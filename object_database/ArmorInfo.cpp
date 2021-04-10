#include "ArmorInfo.h"

namespace object_database {

ArmorInfo::ArmorInfo(ArmorType _type, std::string _name)
    : type(_type), name(std::move(_name)) {

}

const ArmorInfo ArmorInfo::kSoldierStandardArmor
    (ArmorType::kSoldierStandardArmor,
     "soldier_standard_armor");
const ArmorInfo ArmorInfo::kSoldierCompositeArmor
    (ArmorType::kSoldierCompositeArmor,
     "soldier_composite_armor");
const ArmorInfo ArmorInfo::kDroneStandardArmor
    (ArmorType::kDroneStandardArmor,
     "drone_standard_armor");

}
