#pragma once

#include <functional>
#include <sstream>

#include "Widget.h"

namespace widget {

/**
 * Abstract widget representing item selection. Set of items is fixed, not empty and cannot be changed.
 * @tparam Context Type with following associated types: `Context::RenderContext` (used to render widget),
 *                 `Context::ResourcesContext` (resources associated with context).
 */
template<typename Context>
class SelectionWidget : public Widget<Context> {
 private:
  using SelectionChangedListener = std::function<void(SelectionWidget<Context> &)>;

 public:
  /**
   * Creates selection widget using given items. Throws `std::runtime_error` if given array of items is empty.
   * @param items Box items.
   */
  SelectionWidget(std::vector<std::string> items, frontend::Key forward_key, frontend::Key backward_key);

  /** Returns items in widget. */
  const std::vector<std::string> &Items();
  /** Returns index of currently selected item. */
  [[nodiscard]] size_t SelectedItem() const;
  /**
   * Sets index of selected item. Triggers selection change event. Throws `std::runtime_error` if given index is
   * greater or equal to number of items in widget.
   */
  void SetSelectedItem(size_t item);
  /**
   * Moves selection forward by one item if it is possible. Triggers selection change event if selection was moved.
   * Otherwise does nothing.
   */
  void MoveSelectionForward();
  /**
   * Moves selection backward by one item if it is possible. Triggers selection change event if selection was moved.
   * Otherwise does nothing.
   */
  void MoveSelectionBackward();

  /**
   * Adds listener for selection change event.
   * @param listener Listener.
   */
  void AddSelectionChangedListener(SelectionChangedListener listener);

  /**
   * Handles input. If input is left (right) arrow then selection is moved back (forward) if possible. Triggers
   * selection change event if selection was moved and returns true in this case. Otherwise does nothing and returns
   * false.
   * @param input Input to handle.
   */
  bool HandleInput(const frontend::Input &input) override;

 protected:
  /** Array of items. */
  std::vector<std::string> items_;
  /** Current selected item. */
  size_t selected_item_;

 private:
  /** Listeners for selection change event. */
  std::vector<SelectionChangedListener> selection_changed_;
  /** Forward key. */
  frontend::Key forward_key_;
  /** Backward key. */
  frontend::Key backward_key_;

  /**
   * Checks if given item index is valid. Throws `std::runtime_error` if given index is
   * greater or equal to number of items in widget.
   * @param index Index of item.
   */
  void CheckItemIndex(size_t index);
  /** Triggers selection change event. */
  void TriggerSelectionChanged();

};

template<typename Context>
SelectionWidget<Context>::SelectionWidget(std::vector<std::string> items, frontend::Key forward_key,
                                          frontend::Key backward_key)
    : items_(std::move(items)), selected_item_(0), selection_changed_(),
      forward_key_(forward_key), backward_key_(backward_key) {
  if (items_.empty()) {
    throw std::runtime_error("given array of items is empty");
  }
}

template<typename Context>
const std::vector<std::string> &SelectionWidget<Context>::Items() {
  return items_;
}

template<typename Context>
size_t SelectionWidget<Context>::SelectedItem() const {
  return selected_item_;
}

template<typename Context>
void SelectionWidget<Context>::SetSelectedItem(size_t item) {
  CheckItemIndex(item);
  selected_item_ = item;
  TriggerSelectionChanged();
}

template<typename Context>
void SelectionWidget<Context>::MoveSelectionForward() {
  if (selected_item_ + 1 < items_.size()) {
    ++selected_item_;
    TriggerSelectionChanged();
  }
}

template<typename Context>
void SelectionWidget<Context>::MoveSelectionBackward() {
  if (selected_item_ > 0) {
    --selected_item_;
    TriggerSelectionChanged();
  }
}

template<typename Context>
void SelectionWidget<Context>::AddSelectionChangedListener(SelectionWidget::SelectionChangedListener listener) {
  selection_changed_.push_back(listener);
}

template<typename Context>
bool SelectionWidget<Context>::HandleInput(const frontend::Input &input) {
  if (input.IsKey()) {
    frontend::Key key = input.GetKey();
    if (key == forward_key_) {
      MoveSelectionForward();
      return true;
    } else if (key == backward_key_) {
      MoveSelectionBackward();
      return true;
    }
  }

  return false;
}

template<typename Context>
void SelectionWidget<Context>::CheckItemIndex(size_t index) {
  if (index >= items_.size()) {
    std::stringstream message;
    message << "given index (" << index << ") is not in range [0; " << items_.size() << ")";
    throw std::runtime_error(message.str());
  }
}

template<typename Context>
void SelectionWidget<Context>::TriggerSelectionChanged() {
  for (auto &listener : selection_changed_) {
    listener(*this);
  }
}

}
