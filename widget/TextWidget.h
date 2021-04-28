#pragma once

#include "Widget.h"

namespace widget {

/**
 * Widget containing text.
 * @tparam Context Type with following associated types: `Context::RenderContext` (used to render widget),
 *                 `Context::ResourcesContext` (resources associated with context).
 */
template<typename Context>
class TextWidget : public Widget<Context> {
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

  [[nodiscard]] util::Vector2<size_t> MinSize(typename Context::Resources &resources) const override;
  void Render(typename Context::RenderContext &context, typename Context::Resources &resources) override;

 private:
  /** Current text. */
  std::string text_;

};

template<typename Context>
TextWidget<Context>::TextWidget(const std::string &text)
    : text_(text) {

}

template<typename Context>
const std::string &TextWidget<Context>::Text() const {
  return text_;
}

template<typename Context>
void TextWidget<Context>::SetText(const std::string &text) {
  text_ = text;
}

}
