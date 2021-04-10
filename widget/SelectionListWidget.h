#pragma once

#include <functional>
#include <utility>
#include <sstream>

#include "Widget.h"

namespace widget {

/**
 * Widget representing list with item selection. Set of items is fixed, not empty and cannot be changed.
 * @tparam RenderContext Context used to render widget.
 */
template<typename RenderContext>
class SelectionListWidget : public Widget<RenderContext> {
 private:
  using SelectionChangedListener = std::function<void(SelectionListWidget<RenderContext> &)>;

 public:
  /**
   * Creates selection list using given items. Throws `std::runtime_error` if given array of items is empty.
   * @param items List items.
   */
  explicit SelectionListWidget(std::vector<std::string> items);

  /** Returns items in list. */
  const std::vector<std::string> &Items();
  /** Returns index of currently selected item. */
  [[nodiscard]] size_t SelectedItem() const;
  /**
   * Sets index of selected item. Triggers selection change event. Throws `std::runtime_error` if given index is
   * greater or equal to number of items in list.
   */
  void SetSelectedItem(size_t item);
  /**
   * Moves selection up by one item if it is possible. Triggers selection change event if selection was moved.
   * Otherwise does nothing.
   */
  void MoveSelectionUp();
  /**
   * Moves selection down by one item if it is possible. Triggers selection change event if selection was moved.
   * Otherwise does nothing.
   */
  void MoveSelectionDown();

  /**
   * Adds listener for selection change event.
   * @param listener Listener.
   */
  void AddSelectionChangedListener(SelectionChangedListener listener);

  /**
   * Handles input. If input is up (down) arrow then selection is moved up (down) if possible. Triggers selection
   * change event if selection was moved and returns true in this case. Otherwise does nothing and returns false.
   * @param input Input to handle.
   */
  bool HandleInput(const frontend::Input &input) override;
  [[nodiscard]] util::Vector2<size_t> MinSize() const override;
  void Render(RenderContext &context) override;

 private:
  /** Array of items. */
  std::vector<std::string> items_;
  /** Current selected item. */
  size_t selected_item_;
  /** First visible item. Used for rendering. */
  size_t viewed_item_;
  /** Listeners for selection change event. */
  std::vector<SelectionChangedListener> selection_changed_;

  /**
   * Checks if given item index is valid. Throws `std::runtime_error` if given index is
   * greater or equal to number of items in list.
   * @param index Index of item.
   */
  void CheckItemIndex(size_t index);
  /** Triggers selection change event. */
  void TriggerSelectionChanged();

};

/** Alias for shared pointer to selection list widget. */
template<typename RenderContext>
using SelectionListWidgetPtr = std::shared_ptr<SelectionListWidget<RenderContext>>;

template<typename RenderContext>
SelectionListWidget<RenderContext>::SelectionListWidget(std::vector<std::string> items)
    : items_(std::move(items)), selected_item_(0), viewed_item_(0), selection_changed_() {
  if (items_.empty()) {
    throw std::runtime_error("given array of items is empty");
  }
}

template<typename RenderContext>
const std::vector<std::string> &SelectionListWidget<RenderContext>::Items() {
  return items_;
}

template<typename RenderContext>
size_t SelectionListWidget<RenderContext>::SelectedItem() const {
  return selected_item_;
}

template<typename RenderContext>
void SelectionListWidget<RenderContext>::SetSelectedItem(size_t item) {
  CheckItemIndex(item);
  selected_item_ = item;
  TriggerSelectionChanged();
}

template<typename RenderContext>
void SelectionListWidget<RenderContext>::MoveSelectionUp() {
  if (selected_item_ > 0) {
    --selected_item_;
    TriggerSelectionChanged();
  }
}

template<typename RenderContext>
void SelectionListWidget<RenderContext>::MoveSelectionDown() {
  if (selected_item_ + 1 < items_.size()) {
    ++selected_item_;
    TriggerSelectionChanged();
  }
}

template<typename RenderContext>
void SelectionListWidget<RenderContext>::AddSelectionChangedListener(SelectionListWidget::SelectionChangedListener listener) {
  selection_changed_.push_back(listener);
}

template<typename RenderContext>
bool SelectionListWidget<RenderContext>::HandleInput(const frontend::Input &input) {
  if (input.IsKey()) {
    frontend::Key key = input.GetKey();
    if (key == frontend::Key::kUp) {
      MoveSelectionUp();
      return true;
    } else if (key == frontend::kDown) {
      MoveSelectionDown();
      return true;
    }
  }

  return false;
}

template<typename RenderContext>
void SelectionListWidget<RenderContext>::CheckItemIndex(size_t index) {
  if (index >= items_.size()) {
    std::stringstream message;
    message << "given index (" << index << ") is not in range [0; " << items_.size() << ")";
    throw std::runtime_error(message.str());
  }
}

template<typename RenderContext>
void SelectionListWidget<RenderContext>::TriggerSelectionChanged() {
  for (auto &listener : selection_changed_) {
    listener(*this);
  }
}

}
