#include "IRenderSurfaceWrite.h"

namespace frontend::terminal {

void IRenderSurfaceWrite::ClearRectangle(const util::Rectangle<size_t> &rectangle, const CharData &char_data) {
  CheckIfContainsRectangle(rectangle);

  for (size_t row = rectangle.y; row < rectangle.y + rectangle.height; ++row) {
    for (size_t column = rectangle.x; column < rectangle.x + rectangle.width; ++column) {
      Get({column, row}) = char_data;
    }
  }
}

void IRenderSurfaceWrite::Clear(const CharData &char_data) {
  ClearRectangle(Rectangle(), char_data);
}

void IRenderSurfaceWrite::Draw(const IRenderSurfaceRead &surface, const util::Vector2<size_t> &position) {
  util::Vector2<size_t> size = surface.Size();
  util::Rectangle<size_t> target_rectangle{position.x, position.y, size.x, size.y};
  CheckIfContainsRectangle(target_rectangle);

  for (size_t row = 0; row < size.y; ++row) {
    for (size_t column = 0; column < size.x; ++column) {
      Get({column + position.x, row + position.y}) = surface.Get({column, row});
    }
  }
}

}
