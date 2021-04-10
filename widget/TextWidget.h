#pragma once

#include "Widget.h"

namespace widget {

/**
 * Widget containing text.
 * @tparam RenderContext Context used to render widget.
 */
template<typename RenderContext>
class TextWidget : public Widget<RenderContext> {
 public:
  /**
   * Creates text widget using given text.
   * @param text Text.
   */
  explicit TextWidget(const std::string &text);

  /** Returns current text. */
  [[nodiscard]] const std::string &Text() const;
  /**
   * Sets text.
   * @param text Text to set.
   */
  void SetText(const std::string &text);

  [[nodiscard]] util::Vector2<size_t> MinSize() const override;
  void Render(RenderContext &context) override;

 private:
  /** Current text. */
  std::string text_;

};

/** Alias for shared pointer to text widget. */
template<typename RenderContext>
using TextWidgetPtr = std::shared_ptr<TextWidget<RenderContext>>;

template<typename RenderContext>
TextWidget<RenderContext>::TextWidget(const std::string &text)
    : text_(text) {

}

template<typename RenderContext>
const std::string &TextWidget<RenderContext>::Text() const {
  return text_;
}

template<typename RenderContext>
void TextWidget<RenderContext>::SetText(const std::string &text) {
  text_ = text;
}

}
