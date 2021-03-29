#include "SoldierCompositeArmor.h"

namespace unit::soldier::armor {

SoldierCompositeArmor::SoldierCompositeArmor(const config::GameConfig &game_config)
    : BasicArmor(game_config.soldier_composite_armor_defence,
                 game_config.soldier_composite_armor_mass) {

}

}
