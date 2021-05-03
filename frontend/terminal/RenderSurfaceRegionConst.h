#pragma once

#include "IRenderSurfaceRead.h"

namespace frontend::terminal {

/** Const "slice" of other render surface. */
class RenderSurfaceRegionConst : public IRenderSurfaceRead {
 public:
  /**
   * Creates const render surface region wrapping given surface. Checks if given rectangle is contained in given
   * surface, throws `std::runtime_error` if check is failed.
   * @param surface Surface to wrap.
   * @param rectangle Rectangle of given surface corresponding to current surface.
   */
  RenderSurfaceRegionConst(const IRenderSurfaceRead &surface, const util::Rectangle<size_t> &rectangle);

  [[nodiscard]] util::Vector2<size_t> Size() const override;
  [[nodiscard]] const CharData &Get(const util::Vector2<size_t> &position) const override;

 private:
  /** Wrapped surface. */
  const IRenderSurfaceRead &surface_;
  /** Rectangle of wrapped surface corresponding to current surface. */
  util::Rectangle<size_t> rectangle_;

};

}
