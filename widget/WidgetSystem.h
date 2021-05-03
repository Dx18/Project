#pragma once

#include <memory>

#include "Widget.h"

namespace widget {

/**
 * System of widget which is able to store current focused widget, perform input handling.
 * @tparam Context Type with following associated types: `Context::RenderContext` (used to render widget),
 *                 `Context::ResourcesContext` (resources associated with context).
 */
template<typename Context>
class WidgetSystem {
 private:
  using WidgetType = Widget<Context>;
  using WidgetPtr = std::shared_ptr<WidgetType>;
  using WidgetWeakPtr = std::weak_ptr<WidgetType>;

 public:
  WidgetSystem();

  /** Returns true if widget system has root. */
  [[nodiscard]] bool HasRoot() const;
  /** Returns reference to root. Behaviour is undefined if there is no root. */
  WidgetType &Root();
  /**
   * Sets new root.
   * @param root New root.
   */
  void SetRoot(const WidgetPtr &root);
  /**
   * Sets focused widget.
   * @param focused New focused widget.
   */
  void SetFocused(const WidgetWeakPtr &focused);
  /** Resets focus. */
  void ResetFocus();
  /**
   * Handles keyboard input. Returns true if input is successfully handled.
   * @param input Keyboard input.
   */
  bool HandleInput(const frontend::Input &input);

 private:
  /** Root widget. */
  WidgetPtr root_;
  /** Currently focused widget. */
  WidgetWeakPtr focused_;

};

template<typename Context>
WidgetSystem<Context>::WidgetSystem()
    : root_(), focused_() {

}

template<typename Context>
bool WidgetSystem<Context>::HasRoot() const {
  return root_;
}

template<typename Context>
typename WidgetSystem<Context>::WidgetType &WidgetSystem<Context>::Root() {
  return *root_;
}

template<typename Context>
void WidgetSystem<Context>::SetRoot(const WidgetSystem::WidgetPtr &root) {
  root_ = root;
}

template<typename Context>
void WidgetSystem<Context>::SetFocused(const WidgetSystem::WidgetWeakPtr &focused) {
  if (!focused_.expired()) {
    focused_.lock()->SetFocused(false);
  }
  focused_ = focused;
  if (!focused_.expired()) {
    focused_.lock()->SetFocused(true);
  }
}

template<typename Context>
void WidgetSystem<Context>::ResetFocus() {
  SetFocused(nullptr);
}

template<typename Context>
bool WidgetSystem<Context>::HandleInput(const frontend::Input &input) {
  WidgetPtr locked = focused_.lock();
  if (locked) {
    return locked->HandleInput(input);
  }

  return false;
}

}
