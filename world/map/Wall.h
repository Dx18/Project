#pragma once

#include <functional>

#include "WallForm.h"

namespace world::map {

/** Tile wall. */
struct Wall {
  /** Form of wall. */
  WallForm form;

  /**
   * Creates wall using given parameters.
   * @param _form Form of wall.
   */
  explicit Wall(WallForm _form);

  /** Wall equality operator. */
  bool operator==(const Wall &other) const;
  /** Wall inequality operator. */
  bool operator!=(const Wall &other) const;

};

}

namespace std {

template<>
struct hash<world::map::Wall> {
  size_t operator()(const world::map::Wall &wall) const;
};

}
