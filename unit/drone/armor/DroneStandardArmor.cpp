#include "DroneStandardArmor.h"

namespace unit::drone::armor {

using namespace object_database;

DroneStandardArmor::DroneStandardArmor(const config::GameConfig &game_config)
    : BasicArmor(game_config.ArmorDefence(ArmorType::kDroneStandardArmor),
                 game_config.ArmorMass(ArmorType::kDroneStandardArmor)) {

}

}
