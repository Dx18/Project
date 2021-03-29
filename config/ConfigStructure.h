#pragma once

#include <unordered_map>

#include "ConfigSectionStructure.h"

namespace config {

/** Structure of config. Config is formed by sections. Each section stores key-value pairs. */
struct ConfigStructure {
  /** Sections in config. */
  std::unordered_map<std::string, ConfigSectionStructure> sections;
};

}
