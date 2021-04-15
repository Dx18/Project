#include "UnitInfo.h"

namespace object_database {

UnitInfo::UnitInfo(UnitType _type, std::string _name)
    : type(_type), name(std::move(_name)) {

}

const UnitInfo UnitInfo::kSoldier
    (UnitType::kSoldier,
     "soldier");
const UnitInfo UnitInfo::kDrone
    (UnitType::kDrone,
     "drone");

const std::array<UnitInfo, 2> kUnitInfo = {
    UnitInfo::kSoldier,
    UnitInfo::kDrone
};

}
