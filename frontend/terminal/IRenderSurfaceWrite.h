#pragma once

#include <cstdlib>

#include "util/Vector.h"
#include "util/Rectangle.h"

#include "CharData.h"
#include "IRenderSurfaceRead.h"

namespace frontend::terminal {

/** Interface for writing to a render surface. */
class IRenderSurfaceWrite : public IRenderSurfaceRead {
 public:
  /**
   * Returns reference to character data at given position. Position must be contained in render surface
   * rectangle, otherwise method throws `std::runtime_error`.
   * @param position Position of character.
   */
  virtual CharData &Get(const util::Vector2<size_t> &position) = 0;
  /**
   * Clears rectangle of render surface with given character data. Given rectangle must be contained in render
   * surface rectangle, otherwise method throws `std::runtime_error`.
   * @param rectangle Rectangle to clear.
   * @param char_data Character data used to clear.
   */
  virtual void ClearRectangle(const util::Rectangle<size_t> &rectangle, const CharData &char_data);
  /**
   * Clears whole render surface with given character data.
   * @param char_data Character data used to clear.
   */
  virtual void Clear(const CharData &char_data);

};

}
