#include "widget/GridContainerWidget.h"

#include <optional>

#include "frontend/terminal/IRenderSurfaceWrite.h"
#include "frontend/terminal/RenderSurfaceRegion.h"

namespace widget {

using namespace frontend::terminal;

template<>
util::Vector2<size_t> GridContainerWidget<IRenderSurfaceWrite>::MinSize() const {
  size_t min_size_y = 0;
  for (const LinearCell &cell : CreateRowCells()) {
    min_size_y += cell.min_size;
  }
  size_t min_size_x = 0;
  for (const LinearCell &cell : CreateColumnCells()) {
    min_size_x += cell.min_size;
  }

  return {min_size_x, min_size_y};
}

template<>
void GridContainerWidget<IRenderSurfaceWrite>::Render(IRenderSurfaceWrite &context) {
  util::Vector2<size_t> size = context.Size();

  std::vector<size_t> actual_row_sizes;
  ResolveLinearCells(CreateRowCells(), size.y, actual_row_sizes);
  std::vector<size_t> actual_column_sizes;
  ResolveLinearCells(CreateColumnCells(), size.x, actual_column_sizes);

  std::vector<size_t> prefix_row_sizes(actual_row_sizes.size() + 1);
  for (size_t i = 0; i < actual_row_sizes.size(); ++i) {
    prefix_row_sizes[i + 1] = prefix_row_sizes[i] + actual_row_sizes[i];
  }
  std::vector<size_t> prefix_column_sizes(actual_column_sizes.size() + 1);
  for (size_t j = 0; j < actual_column_sizes.size(); ++j) {
    prefix_column_sizes[j + 1] = prefix_column_sizes[j] + actual_column_sizes[j];
  }

  for (size_t i = 0; i < actual_row_sizes.size(); ++i) {
    for (size_t j = 0; j < actual_column_sizes.size(); ++j) {
      util::Rectangle<size_t> rectangle = {
          prefix_column_sizes[j],
          prefix_row_sizes[i],
          prefix_column_sizes[j + 1] - prefix_column_sizes[j],
          prefix_row_sizes[i + 1] - prefix_row_sizes[i]
      };

      RenderSurfaceRegion region(context, rectangle);
      widgets_[GetSlotIndex({j, i})]->Render(region);
    }
  }
}

}
