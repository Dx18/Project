#include "widget/SelectionListWidget.h"

#include "frontend/terminal/IRenderSurfaceWrite.h"
#include "util/Math.h"

namespace widget {

using namespace frontend::terminal;

template<>
util::Vector2<size_t> SelectionListWidget<IRenderSurfaceWrite>::MinSize() const {
  static const size_t kMarkerSize = 1;
  static const size_t kGapSize = 1;
  static const size_t kMinTextLength = 1;
  static const size_t kMinItems = 1;
  return {kMarkerSize + kGapSize + kMinTextLength, kMinItems};
}

template<>
void SelectionListWidget<IRenderSurfaceWrite>::Render(IRenderSurfaceWrite &context) {
  util::Vector2<size_t> size = context.Size();

  if (size.y == 0) {
    return;
  }

  {
    size_t max_distance = size.y - 1;
    viewed_item_ = util::math::clamp(viewed_item_,
                                     selected_item_ > max_distance ? selected_item_ - max_distance : 0,
                                     selected_item_ + max_distance);
  }

  size_t item_begin = viewed_item_;
  size_t item_end = std::min(items_.size(), viewed_item_ + size.y);

  ColorPair normal_color(Color::kWhite, Color::kBlack);
  ColorPair selected_color(Color::kYellow, Color::kBlack);

  if (focused_) {
    selected_color = selected_color.Inverted();
  }

  for (size_t item = item_begin; item < item_end; ++item) {
    ColorPair color = item == selected_item_ ? selected_color : normal_color;

    if (size.x == 0) {
      continue;
    }

    if (item == selected_item_) {
      context.Get({0, item - item_begin}) = CharData('>', color);
    }

    if (size.x <= 2) {
      continue;
    }

    size_t chars_to_render = std::min(items_[item].size(), size.x - 2);
    for (size_t i = 0; i < chars_to_render; ++i) {
      context.Get({2 + i, item - item_begin}) = CharData(items_[item][i], color);
    }
  }
}

}
