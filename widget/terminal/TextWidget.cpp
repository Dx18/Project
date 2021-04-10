#include "widget/TextWidget.h"

#include "frontend/terminal/IRenderSurfaceWrite.h"

namespace widget {

using namespace frontend::terminal;

template<>
util::Vector2<size_t> TextWidget<IRenderSurfaceWrite>::MinSize() const {
  return {text_.size(), 1};
}

template<>
void widget::TextWidget<frontend::terminal::IRenderSurfaceWrite>::Render(frontend::terminal::IRenderSurfaceWrite &context) {
  using namespace frontend::terminal;

  size_t chars_to_render = std::min(text_.size(), context.Size().x);
  ColorPair color(Color::kWhite, Color::kBlack);
  for (size_t i = 0; i < chars_to_render; ++i) {
    context.Get({i, 0}) = CharData(text_[i], color);
  }
}

}