#pragma once

#include "SelectionWidget.h"

namespace widget {

/**
 * Widget representing list with item selection. Set of items is fixed, not empty and cannot be changed.
 * @tparam RenderContext Context used to render widget.
 */
template<typename RenderContext>
class SelectionListWidget : public SelectionWidget<RenderContext> {
 public:
  /**
   * Creates selection list using given items. Throws `std::runtime_error` if given array of items is empty.
   * @param items List items.
   */
  explicit SelectionListWidget(const std::vector<std::string> &items);

  [[nodiscard]] util::Vector2<size_t> MinSize() const override;
  void Render(RenderContext &context) override;

 private:
  /** First visible item. Used for rendering. */
  size_t viewed_item_;

};

template<typename RenderContext>
SelectionListWidget<RenderContext>::SelectionListWidget(const std::vector<std::string> &items)
    : SelectionWidget<RenderContext>(items, frontend::Key::kDown, frontend::Key::kUp),
      viewed_item_(0) {

}

}
