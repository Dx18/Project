#pragma once

namespace headquarters_model::armory {

/** Result of weapon/armor building. */
enum BuildResult {
  /** Weapon/armor was successfully built. */
  kBuilt,
  /** Not enough resources for building. */
  kNotEnoughResources
};

}
