#pragma once

#include "IRenderSurfaceWrite.h"

namespace frontend::terminal {

/** Editable "slice" of other render surface. */
class RenderSurfaceRegion : public IRenderSurfaceWrite {
 public:
  /**
   * Creates render surface region wrapping given surface. Checks if given rectangle is contained in given
   * surface, throws `std::runtime_error` if check is failed.
   * @param surface Surface to wrap.
   * @param rectangle Rectangle of given surface corresponding to current surface.
   */
  RenderSurfaceRegion(IRenderSurfaceWrite &surface, const util::Rectangle<size_t> &rectangle);

  [[nodiscard]] util::Vector2<size_t> Size() const override;
  [[nodiscard]] const CharData &Get(const util::Vector2<size_t> &position) const override;
  CharData &Get(const util::Vector2<size_t> &position) override;

 private:
  /** Wrapped surface. */
  IRenderSurfaceWrite &surface_;
  /** Rectangle of wrapped surface corresponding to current surface. */
  util::Rectangle<size_t> rectangle_;

};

}
