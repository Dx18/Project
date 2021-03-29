#include "DroneStandardArmor.h"

namespace unit::drone::armor {

DroneStandardArmor::DroneStandardArmor(const config::GameConfig &game_config)
    : BasicArmor(game_config.drone_standard_armor_defence,
                 game_config.drone_standard_armor_mass) {

}

}
