#include "ArmorInfo.h"

namespace object_database {

ArmorInfo::ArmorInfo(ArmorType _type, ArmorTechType _tech_type, std::string _name)
    : type(_type), tech_type(_tech_type), name(std::move(_name)) {

}

const ArmorInfo ArmorInfo::kSoldierStandardArmor
    (ArmorType::kSoldierStandardArmor,
     ArmorTechType::kStandard,
     "soldier_standard_armor");
const ArmorInfo ArmorInfo::kSoldierCompositeArmor
    (ArmorType::kSoldierCompositeArmor,
     ArmorTechType::kComposite,
     "soldier_composite_armor");
const ArmorInfo ArmorInfo::kDroneStandardArmor
    (ArmorType::kDroneStandardArmor,
     ArmorTechType::kStandard,
     "drone_standard_armor");
const ArmorInfo ArmorInfo::kDroneCompositeArmor
    (ArmorType::kDroneCompositeArmor,
     ArmorTechType::kComposite,
     "drone_composite_armor");

const std::array<ArmorInfo, 4> kArmorInfo = {
    ArmorInfo::kSoldierStandardArmor,
    ArmorInfo::kSoldierCompositeArmor,
    ArmorInfo::kDroneStandardArmor,
    ArmorInfo::kDroneCompositeArmor
};

}
