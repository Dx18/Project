#include "RenderSurfaceRegion.h"

namespace frontend::terminal {

RenderSurfaceRegion::RenderSurfaceRegion(IRenderSurfaceWrite &surface, const util::Rectangle<size_t> &rectangle)
    : surface_(surface), rectangle_(rectangle) {
  surface_.CheckIfContainsRectangle(rectangle_);
}

util::Vector2<size_t> RenderSurfaceRegion::Size() const {
  return {rectangle_.width, rectangle_.height};
}

const CharData &RenderSurfaceRegion::Get(const util::Vector2<size_t> &position) const {
  CheckIfContainsPoint(position);
  return surface_.Get({position.x + rectangle_.x, position.y + rectangle_.y});
}

CharData &RenderSurfaceRegion::Get(const util::Vector2<size_t> &position) {
  CheckIfContainsPoint(position);
  return surface_.Get({position.x + rectangle_.x, position.y + rectangle_.y});
}

}
