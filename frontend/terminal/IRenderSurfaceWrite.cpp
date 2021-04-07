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

}
