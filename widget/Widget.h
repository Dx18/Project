#pragma once

#include <memory>

#include "util/Vector.h"
#include "frontend/Input.h"

namespace widget {

/**
 * Abstract widget.
 * @tparam Context Type with following associated types: `Context::RenderContext` (used to render widget),
 *                 `Context::ResourcesContext` (resources associated with context).
 */
template<typename Context>
class Widget {
 public:
  /** Creates widget with default parameters. */
  Widget();

  virtual ~Widget() = 0;

  /** Returns expanding preference of current widget. */
  [[nodiscard]] virtual util::Vector2<bool> PreferExpand() const;
  /**
   * Sets expanding preference of current widget.
   * @param expand Expanding preference.
   */
  virtual void SetPreferExpand(const util::Vector2<bool> &expand);

  /** Returns true if widget is currently focused. */
  [[nodiscard]] virtual bool Focused() const;
  /**
   * Sets focus state of current widget.
   * @param focused True if widget is focused. Otherwise false.
   */
  virtual void SetFocused(bool focused);

  /** Returns weak pointer to parent of current widget. */
  [[nodiscard]] virtual const std::weak_ptr<Widget<Context>> &Parent() const;
  /**
   * Sets parent of current widget.
   * @param parent Weak pointer to new parent of current widget.
   */
  virtual void SetParent(const std::weak_ptr<Widget<Context>> &parent);

  /**
   * Handles keyboard input. Returns true if input is successfully handled.
   * @param input Input to handle.
   */
  virtual bool HandleInput(const frontend::Input &input);

  /** Returns minimum possible size current widget can occupy. Behaviour of this method depends on render context. */
  [[nodiscard]] virtual util::Vector2<size_t> MinSize(typename Context::Resources &resources) const = 0;
  /**
   * Renders widget using given render context. Behaviour of this method depends on render context. This method must
   * be specialized by every render context.
   * @param context Render context.
   */
  virtual void Render(typename Context::RenderContext &context, typename Context::Resources &resources) = 0;

 protected:
  /** Expanding preference. */
  util::Vector2<bool> expand_;
  /** True if current widget is currently focused. Otherwise false. */
  bool focused_;
  /** Weak pointer to parent of current widget. */
  std::weak_ptr<Widget<Context>> parent_;

};

template<typename Context>
Widget<Context>::Widget()
    : expand_({false, false}), focused_(false), parent_() {

}

template<typename Context>
Widget<Context>::~Widget() = default;

template<typename Context>
util::Vector2<bool> Widget<Context>::PreferExpand() const {
  return expand_;
}

template<typename Context>
void Widget<Context>::SetPreferExpand(const util::Vector2<bool> &expand) {
  expand_ = expand;
}

template<typename Context>
bool Widget<Context>::Focused() const {
  return focused_;
}

template<typename Context>
void Widget<Context>::SetFocused(bool focused) {
  focused_ = focused;
}

template<typename Context>
const std::weak_ptr<Widget<Context>> &Widget<Context>::Parent() const {
  return parent_;
}

template<typename Context>
void Widget<Context>::SetParent(const std::weak_ptr<Widget<Context>> &parent) {
  parent_ = parent;
}

template<typename Context>
bool Widget<Context>::HandleInput(const frontend::Input &input) {
  return false;
}

}
