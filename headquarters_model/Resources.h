#pragma once

#include "config/ConfigSectionStructure.h"

namespace headquarters_model {

/** Headquarters resources. */
struct Resources {
  /** Available amount of matter. */
  int matter;

  /** Creates default headquarters resources. */
  Resources();

  /**
   * Creates resources using given info about resources.
   * @param resources_info Info about resources.
   */
  explicit Resources(const config::ConfigSectionStructure &resources_info);
};

}
