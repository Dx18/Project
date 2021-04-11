#include "DroneStandardArmor.h"

namespace unit::drone::armor {

using namespace object_database;

DroneStandardArmor::DroneStandardArmor(const Tech &tech)
    : BasicArmor(tech.ArmorDefence(ArmorType::kDroneStandardArmor),
                 tech.ArmorMass(ArmorType::kDroneStandardArmor)) {

}

}
