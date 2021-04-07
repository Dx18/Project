#include "IRenderSurfaceRead.h"

namespace frontend::terminal {

IRenderSurfaceRead::~IRenderSurfaceRead() = default;

util::Rectangle<size_t> IRenderSurfaceRead::Rectangle() const {
  util::Vector2<size_t> size = Size();
  return {0, 0, size.x, size.y};
}

void IRenderSurfaceRead::CheckIfContainsRectangle(const util::Rectangle<size_t> &rectangle) const {
  util::Rectangle<size_t> current_rectangle = Rectangle();
  if (!current_rectangle.ContainsRectangle(rectangle)) {
    std::stringstream message;
    message << "surface with rectangle " << current_rectangle << " does not contain given rectangle " << rectangle;
    throw std::runtime_error(message.str());
  }
}

void IRenderSurfaceRead::CheckIfContainsPoint(const util::Vector2<size_t> &point) const {
  util::Rectangle<size_t> current_rectangle = Rectangle();
  if (!current_rectangle.ContainsPoint(point)) {
    std::stringstream message;
    message << "surface with rectangle " << current_rectangle << " does not contain given point " << point;
    throw std::runtime_error(message.str());
  }
}

}
