#include "RenderSurfaceRegionConst.h"

namespace frontend::terminal {

RenderSurfaceRegionConst::RenderSurfaceRegionConst(const IRenderSurfaceRead &surface,
                                                   const util::Rectangle<size_t> &rectangle)
    : surface_(surface), rectangle_(rectangle) {
  surface_.CheckIfContainsRectangle(rectangle);
}

util::Vector2<size_t> RenderSurfaceRegionConst::Size() const {
  return {rectangle_.width, rectangle_.height};
}

const CharData & RenderSurfaceRegionConst::Get(const util::Vector2<size_t> &position) const {
  CheckIfContainsPoint(position);
  return surface_.Get({position.x + rectangle_.x, position.y + rectangle_.y});
}

}
