#pragma once

#include "SelectionWidget.h"

namespace widget {

/**
 * Widget representing box with item selection. Set of items is fixed, not empty and cannot be changed.
 * @tparam Context Type with following associated types: `Context::RenderContext` (used to render widget),
 *                 `Context::ResourcesContext` (resources associated with context).
 */
template<typename Context>
class SelectionBoxWidget : public SelectionWidget<Context> {
 public:
  /**
   * Creates selection box using given items. Throws `std::runtime_error` if given array of items is empty.
   * @param items List items.
   */
  explicit SelectionBoxWidget(const std::vector<std::string> &items);

  [[nodiscard]] util::Vector2<size_t> MinSize(typename Context::Resources &resources) const override;
  void Render(typename Context::RenderContext &context, typename Context::Resources &resources) override;

 private:
  /** Max length of item. */
  size_t max_item_size_;

};

template<typename Context>
SelectionBoxWidget<Context>::SelectionBoxWidget(const std::vector<std::string> &items)
    : SelectionWidget<Context>(items, frontend::Key::kRight, frontend::Key::kLeft) {
  max_item_size_ = std::max_element(SelectionWidget<Context>::items_.begin(),
                                    SelectionWidget<Context>::items_.end(),
                                    [](const std::string &item1, const std::string &item2) {
                                      return item1.size() < item2.size();
                                    })->size();
}

}
