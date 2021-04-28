#pragma once

#include <string>
#include <array>

#include "FloorMaterialType.h"

namespace world {

/** Floor material. */
class FloorMaterial {
 public:
  /** Wooden floor. */
  static const FloorMaterial kWood;
  /** Grass. */
  static const FloorMaterial kGrass;
  /** Asphalt. */
  static const FloorMaterial kAsphalt;

  /** Type of floor material. */
  const FloorMaterialType type;
  /** Name of floor material. */
  const std::string name;

 private:
  /**
   * Creates floor material.
   * @param _type Type of floor material.
   * @param _name Name of floor material.
   */
  FloorMaterial(FloorMaterialType _type, std::string _name);

};

/** Available floor materials. `FloorMaterialType` can be used as index of this array. */
extern const std::array<FloorMaterial, 3> kFloorMaterial;

}
