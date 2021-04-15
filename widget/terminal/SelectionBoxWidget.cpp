#include "widget/SelectionBoxWidget.h"

#include "frontend/terminal/IRenderSurfaceWrite.h"

namespace widget {

using namespace frontend::terminal;

template<>
util::Vector2<size_t> SelectionBoxWidget<IRenderSurfaceWrite>::MinSize() const {
  static const size_t kMarkerSize = 1;
  const size_t max_item_size = std::max_element(items_.begin(), items_.end(),
                                                [](const std::string &item1, const std::string &item2) {
                                                  return item1.size() < item2.size();
                                                })->size();
  return {2 * kMarkerSize + max_item_size, 1};
}

template<>
void SelectionBoxWidget<IRenderSurfaceWrite>::Render(IRenderSurfaceWrite &context) {
  util::Vector2<size_t> size = context.Size();

  if (size.y == 0 || size.x <= 2) {
    return;
  }

  ColorPair marker_disabled_color(Color::kWhite, Color::kBlack);
  ColorPair marker_enabled_color(Color::kYellow, Color::kBlack);
  ColorPair text_color(Color::kWhite, Color::kBlack);

  context.Get(util::Vector2<size_t>{0, 0})
      = CharData('<', selected_item_ == 0 ? marker_disabled_color : marker_enabled_color);
  context.Get(util::Vector2<size_t>{std::min(size.x - 1, 1 + max_item_size_), 0})
      = CharData('>', selected_item_ == items_.size() - 1 ? marker_disabled_color : marker_enabled_color);

  size_t chars_to_draw = std::min(size.x - 2, items_[selected_item_].size());
  for (size_t i = 0; i < chars_to_draw; ++i) {
    context.Get(util::Vector2<size_t>{1 + i, 0})
        = CharData(items_[selected_item_][i], text_color);
  }
}

}
