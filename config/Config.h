#pragma once

#include "ConfigStructure.h"
#include "GameConfig.h"

namespace config {

/** Application config. */
struct Config {
  /** Game process config. */
  GameConfig game_config;

  /** Creates config from given structure. May throw an exception. */
  explicit Config(const ConfigStructure &config_structure);

};

}
