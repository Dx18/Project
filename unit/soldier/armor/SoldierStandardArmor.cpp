#include "SoldierStandardArmor.h"

namespace unit::soldier::armor {

using namespace object_database;

SoldierStandardArmor::SoldierStandardArmor(const config::GameConfig &game_config)
    : BasicArmor(game_config.ArmorDefence(ArmorType::kSoldierStandardArmor),
                 game_config.ArmorMass(ArmorType::kSoldierStandardArmor)) {

}

}
