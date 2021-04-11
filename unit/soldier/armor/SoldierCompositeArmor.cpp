#include "SoldierCompositeArmor.h"

namespace unit::soldier::armor {

using namespace object_database;

SoldierCompositeArmor::SoldierCompositeArmor(const Tech &tech)
    : BasicArmor(tech.ArmorDefence(ArmorType::kSoldierCompositeArmor),
                 tech.ArmorMass(ArmorType::kSoldierCompositeArmor)) {

}

}
