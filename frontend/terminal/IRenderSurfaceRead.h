#pragma once

#include <cstdlib>
#include <stdexcept>
#include <sstream>

#include "util/Vector.h"
#include "util/Rectangle.h"

#include "CharData.h"

namespace frontend::terminal {

/** Interface for reading to a render surface. */
class IRenderSurfaceRead {
 public:
  virtual ~IRenderSurfaceRead() = 0;

  /** Returns size of render surface. */
  [[nodiscard]] virtual util::Vector2<size_t> Size() const = 0;
  /**
   * Returns const reference to character data at given position. Position must be contained in render surface
   * rectangle, otherwise method throws `std::runtime_error`.
   * @param position Position of character.
   */
  [[nodiscard]] virtual const CharData &Get(const util::Vector2<size_t> &position) const = 0;
  /** Returns render surface rectangle: rectangle of size equal to size of current render surface beginning at (0, 0) */
  [[nodiscard]] virtual util::Rectangle<size_t> Rectangle() const;

  /**
   * Checks if current surface contains given rectangle. Throws instance of `std::runtime_error` if check is failed.
   * @param rectangle Rectangle to check.
   */
  void CheckIfContainsRectangle(const util::Rectangle<size_t> &rectangle) const;
  /**
   * Checks if current surface contains given point. Throws instance of `std::runtime_error` if check is failed.
   * @param point Point to check.
   */
  void CheckIfContainsPoint(const util::Vector2<size_t> &point) const;

};

}
