#include "SoldierCompositeArmor.h"

namespace unit::soldier::armor {

using namespace object_database;

SoldierCompositeArmor::SoldierCompositeArmor(const config::GameConfig &game_config)
    : BasicArmor(game_config.ArmorDefence(ArmorType::kSoldierCompositeArmor),
                 game_config.ArmorMass(ArmorType::kSoldierCompositeArmor)) {

}

}
