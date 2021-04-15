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
  if (render_separators_ && dimensions_.y > 0) {
    min_size_y += dimensions_.y - 1;
  }

  size_t min_size_x = 0;
  for (const LinearCell &cell : CreateColumnCells()) {
    min_size_x += cell.min_size;
  }
  if (render_separators_ && dimensions_.x > 0) {
    min_size_x += dimensions_.x - 1;
  }

  return {min_size_x, min_size_y};
}

template<>
void GridContainerWidget<IRenderSurfaceWrite>::Render(IRenderSurfaceWrite &context) {
  util::Vector2<size_t> size = context.Size();

  if (render_separators_ && (dimensions_.y > size.y + 1 || dimensions_.x > size.x + 1)) {
    return;
  }

  size_t available_height = size.y - (render_separators_ ? 1 : 0) * (dimensions_.y - 1);
  size_t available_width = size.x - (render_separators_ ? 1 : 0) * (dimensions_.x - 1);

  std::vector<size_t> actual_row_sizes;
  ResolveLinearCells(CreateRowCells(), available_height, actual_row_sizes);
  std::vector<size_t> actual_column_sizes;
  ResolveLinearCells(CreateColumnCells(), available_width, actual_column_sizes);

  std::vector<size_t> prefix_row_sizes(actual_row_sizes.size() + 1);
  for (size_t i = 0; i < actual_row_sizes.size(); ++i) {
    prefix_row_sizes[i + 1] = prefix_row_sizes[i] + actual_row_sizes[i];
  }
  std::vector<size_t> prefix_column_sizes(actual_column_sizes.size() + 1);
  for (size_t j = 0; j < actual_column_sizes.size(); ++j) {
    prefix_column_sizes[j + 1] = prefix_column_sizes[j] + actual_column_sizes[j];
  }

  if (actual_row_sizes.empty() || actual_column_sizes.empty()) {
    return;
  }

  if (render_separators_) {
    ColorPair color(Color::kWhite, Color::kBlack);

    for (size_t i = 0; i < actual_row_sizes.size() - 1; ++i) {
      for (size_t j = 0; j < size.x; ++j) {
        context.Get({j, prefix_row_sizes[i + 1] + i}) = CharData('-', color);
      }
    }
    for (size_t j = 0; j < actual_column_sizes.size() - 1; ++j) {
      for (size_t i = 0; i < size.y; ++i) {
        context.Get({prefix_column_sizes[j + 1] + j, i}) = CharData('|', color);
      }
    }
    for (size_t i = 0; i < actual_row_sizes.size() - 1; ++i) {
      for (size_t j = 0; j < actual_column_sizes.size() - 1; ++j) {
        context.Get({prefix_column_sizes[j + 1] + j, prefix_row_sizes[i + 1] + i}) = CharData('+', color);
      }
    }
  }

  for (size_t i = 0; i < actual_row_sizes.size(); ++i) {
    for (size_t j = 0; j < actual_column_sizes.size(); ++j) {
      util::Rectangle<size_t> rectangle = {
          prefix_column_sizes[j] + (render_separators_ ? j : 0),
          prefix_row_sizes[i] + (render_separators_ ? i : 0),
          prefix_column_sizes[j + 1] - prefix_column_sizes[j],
          prefix_row_sizes[i + 1] - prefix_row_sizes[i]
      };

      RenderSurfaceRegion region(context, rectangle);
      WidgetPtr widget = widgets_[GetSlotIndex({j, i})];
      if (widget) {
        widget->Render(region);
      }
    }
  }
}

}
