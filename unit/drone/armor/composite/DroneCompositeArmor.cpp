#include "DroneCompositeArmor.h"

namespace unit::drone::armor::composite {

using namespace object_database;

DroneCompositeArmor::DroneCompositeArmor(const Tech &tech)
    : BasicArmor(tech.ArmorDefence(ArmorType::kDroneCompositeArmor),
                 tech.ArmorMass(ArmorType::kDroneCompositeArmor)) {

}

}
