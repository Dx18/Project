#pragma once

#include "SelectionWidget.h"

namespace widget {

/**
 * Widget representing list with item selection. Set of items is fixed, not empty and cannot be changed.
 * @tparam Context Type with following associated types: `Context::RenderContext` (used to render widget),
 *                 `Context::ResourcesContext` (resources associated with context).
 */
template<typename Context>
class SelectionListWidget : public SelectionWidget<Context> {
 public:
  /**
   * Creates selection list using given items. Throws `std::runtime_error` if given array of items is empty.
   * @param items List items.
   */
  explicit SelectionListWidget(const std::vector<std::string> &items);

  [[nodiscard]] util::Vector2<size_t> MinSize(typename Context::Resources &resources) const override;
  void Render(typename Context::RenderContext &context, typename Context::Resources &resources) override;

 private:
  /** First visible item. Used for rendering. */
  size_t viewed_item_;

};

template<typename Context>
SelectionListWidget<Context>::SelectionListWidget(const std::vector<std::string> &items)
    : SelectionWidget<Context>(items, frontend::Key::kDown, frontend::Key::kUp),
      viewed_item_(0) {

}

}
