#include "SoldierStandardArmor.h"

namespace unit::soldier::armor {

SoldierStandardArmor::SoldierStandardArmor(const config::GameConfig &game_config)
    : BasicArmor(game_config.soldier_standard_armor_defence,
                 game_config.soldier_standard_armor_mass) {

}

}
