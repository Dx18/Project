#include "Config.h"

namespace config {

Config::Config(const ConfigStructure &config)
    : game_config(config.sections.at("Game")) {

}

}
