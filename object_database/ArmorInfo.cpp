#include "ArmorInfo.h"

namespace object_database {

ArmorInfo::ArmorInfo(ArmorType _type, ArmorTechType _tech_type, UnitType _unit_type, std::string _name)
    : type(_type), tech_type(_tech_type), unit_type(_unit_type), name(std::move(_name)) {

}

const ArmorInfo ArmorInfo::kSoldierStandardArmor
    (ArmorType::kSoldierStandardArmor,
     ArmorTechType::kStandard,
     UnitType::kSoldier,
     "soldier_standard_armor");
const ArmorInfo ArmorInfo::kSoldierCompositeArmor
    (ArmorType::kSoldierCompositeArmor,
     ArmorTechType::kComposite,
     UnitType::kSoldier,
     "soldier_composite_armor");
const ArmorInfo ArmorInfo::kDroneStandardArmor
    (ArmorType::kDroneStandardArmor,
     ArmorTechType::kStandard,
     UnitType::kDrone,
     "drone_standard_armor");
const ArmorInfo ArmorInfo::kDroneCompositeArmor
    (ArmorType::kDroneCompositeArmor,
     ArmorTechType::kComposite,
     UnitType::kDrone,
     "drone_composite_armor");

const std::array<ArmorInfo, 4> kArmorInfo = {
    ArmorInfo::kSoldierStandardArmor,
    ArmorInfo::kSoldierCompositeArmor,
    ArmorInfo::kDroneStandardArmor,
    ArmorInfo::kDroneCompositeArmor
};

}
