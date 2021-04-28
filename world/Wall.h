#pragma once

#include <functional>

#include "WallForm.h"

namespace world {

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
struct hash<world::Wall> {
  size_t operator()(const world::Wall &wall) const;
};

}
