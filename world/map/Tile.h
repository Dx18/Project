#pragma once

#include <array>
#include <functional>

#include "Wall.h"
#include "FloorMaterialType.h"

namespace world::map {

/** World tile. */
struct Tile {
  /** Number of walls. */
  static const size_t kWallCount = 4;

  /** Tile walls. */
  std::array<Wall, kWallCount> walls;
  /** Floor material. */
  FloorMaterialType floor;

  /**
   * Creates tile using given parameters.
   * @param _walls Tile walls.
   * @param _floor Floor material.
   */
  Tile(std::array<Wall, kWallCount> _walls, FloorMaterialType _floor);

  /** Tile equality operator. */
  bool operator==(const Tile &other) const;
  /** Tile inequality operator. */
  bool operator!=(const Tile &other) const;

};

}

namespace std {

template<>
struct hash<world::map::Tile> {
  size_t operator()(const world::map::Tile &tile) const;
};

}
