#include "SoldierStandardArmor.h"

namespace unit::soldier::armor {

using namespace object_database;

SoldierStandardArmor::SoldierStandardArmor(const Tech &tech)
    : BasicArmor(tech.ArmorDefence(ArmorType::kSoldierStandardArmor),
                 tech.ArmorMass(ArmorType::kSoldierStandardArmor)) {

}

}
