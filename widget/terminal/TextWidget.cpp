#include "widget/TextWidget.h"

#include "frontend/terminal/IRenderSurfaceWrite.h"

namespace widget {

using namespace frontend::terminal;

template<>
util::Vector2<size_t> TextWidget<IRenderSurfaceWrite>::MinSize() const {
  if (text_.empty()) {
    return {1, 1};
  }
  size_t line_count = 1;
  size_t line_length = 0;
  size_t max_line_length = 0;
  for (char ch : text_) {
    if (ch == '\n') {
      max_line_length = std::max(max_line_length, line_length);
      line_length = 0;
      ++line_count;
    } else {
      ++line_length;
    }
  }
  max_line_length = std::max(max_line_length, line_length);

  return {max_line_length, line_count};
}

template<>
void widget::TextWidget<frontend::terminal::IRenderSurfaceWrite>::Render(frontend::terminal::IRenderSurfaceWrite &context) {
  using namespace frontend::terminal;

  util::Vector2<size_t> size = context.Size();

  size_t row = 0;
  size_t column = 0;
  ColorPair color(Color::kWhite, Color::kBlack);
  for (char ch : text_) {
    if (ch == '\n') {
      column = 0;
      ++row;
    } else {
      if (column < size.x && row < size.y) {
        context.Get({column, row}) = CharData(ch, color);
      }
      ++column;
    }
  }
}

}