#include "ArmorTechInfo.h"

namespace object_database {

ArmorTechInfo::ArmorTechInfo(ArmorTechType _tech_type, std::string _name)
    : tech_type(_tech_type), name(std::move(_name)) {

}

const ArmorTechInfo ArmorTechInfo::kStandard
    (ArmorTechType::kStandard,
     "standard_armor");
const ArmorTechInfo ArmorTechInfo::kComposite
    (ArmorTechType::kComposite,
     "composite_armor");

const std::array<ArmorTechInfo, 2> kArmorTechInfo = {
    ArmorTechInfo::kStandard,
    ArmorTechInfo::kComposite
};

}
