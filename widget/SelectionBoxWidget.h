#pragma once

#include "SelectionWidget.h"

namespace widget {

/**
 * Widget representing box with item selection. Set of items is fixed, not empty and cannot be changed.
 * @tparam RenderContext Context used to render widget.
 */
template<typename RenderContext>
class SelectionBoxWidget : public SelectionWidget<RenderContext> {
 public:
  /**
   * Creates selection box using given items. Throws `std::runtime_error` if given array of items is empty.
   * @param items List items.
   */
  explicit SelectionBoxWidget(const std::vector<std::string> &items);

  [[nodiscard]] util::Vector2<size_t> MinSize() const override;
  void Render(RenderContext &context) override;

 private:
  /** Max length of item. */
  size_t max_item_size_;

};

template<typename RenderContext>
SelectionBoxWidget<RenderContext>::SelectionBoxWidget(const std::vector<std::string> &items)
    : SelectionWidget<RenderContext>(items, frontend::Key::kRight, frontend::Key::kLeft) {
  max_item_size_ = std::max_element(SelectionWidget<RenderContext>::items_.begin(),
                                    SelectionWidget<RenderContext>::items_.end(),
                                    [](const std::string &item1, const std::string &item2) {
                                      return item1.size() < item2.size();
                                    })->size();
}

}
