#pragma once

#include <unordered_map>
#include <string>
#include <sstream>

namespace config {

/** Structure of section in config. */
struct ConfigSectionStructure {
  /** Key-value pairs in section. */
  std::unordered_map<std::string, std::string> values;
};

}
