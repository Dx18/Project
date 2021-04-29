#pragma once

#include <algorithm>

#include "IConfigStructureReader.h"

namespace config {

/** Reader for config structure stored in INI format. */
class INIConfigStructureReader : public IConfigStructureReader {
 public:
  ConfigStructure Read(std::istream &input) override;

};

}
