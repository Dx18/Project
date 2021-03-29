#pragma once

#include "ConfigStructure.h"

namespace config {

/** Reader for config structure. */
class IConfigStructureReader {
 public:
  virtual ~IConfigStructureReader() = default;

  /**
   * Reads config structure from given input stream.
   * @param input Input stream.
   */
  virtual ConfigStructure Read(std::istream &input) = 0;

};

}
