#pragma once

#include <memory>

#include "util/Vector.h"
#include "frontend/Input.h"

namespace widget {

/**
 * Abstract widget.
 * @tparam RenderContext Context used to render widget.
 */
template<typename RenderContext>
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
  [[nodiscard]] virtual const std::weak_ptr<Widget<RenderContext>> &Parent() const;
  /**
   * Sets parent of current widget.
   * @param parent Weak pointer to new parent of current widget.
   */
  virtual void SetParent(const std::weak_ptr<Widget<RenderContext>> &parent);

  /**
   * Handles keyboard input. Returns true if input is successfully handled.
   * @param input Input to handle.
   */
  virtual bool HandleInput(const frontend::Input &input);

  /** Returns minimum possible size current widget can occupy. Behaviour of this method depends on render context. */
  [[nodiscard]] virtual util::Vector2<size_t> MinSize() const = 0;
  /**
   * Renders widget using given render context. Behaviour of this method depends on render context. This method must
   * be specialized by every render context.
   * @param context Render context.
   */
  virtual void Render(RenderContext &context) = 0;

 protected:
  /** Expanding preference. */
  util::Vector2<bool> expand_;
  /** True if current widget is currently focused. Otherwise false. */
  bool focused_;
  /** Weak pointer to parent of current widget. */
  std::weak_ptr<Widget<RenderContext>> parent_;

};

template<typename RenderContext>
Widget<RenderContext>::Widget()
    : expand_({false, false}), focused_(false), parent_() {

}

template<typename RenderContext>
Widget<RenderContext>::~Widget() = default;

template<typename RenderContext>
util::Vector2<bool> Widget<RenderContext>::PreferExpand() const {
  return expand_;
}

template<typename RenderContext>
void Widget<RenderContext>::SetPreferExpand(const util::Vector2<bool> &expand) {
  expand_ = expand;
}

template<typename RenderContext>
bool Widget<RenderContext>::Focused() const {
  return focused_;
}

template<typename RenderContext>
void Widget<RenderContext>::SetFocused(bool focused) {
  focused_ = focused;
}

template<typename RenderContext>
const std::weak_ptr<Widget<RenderContext>> &Widget<RenderContext>::Parent() const {
  return parent_;
}

template<typename RenderContext>
void Widget<RenderContext>::SetParent(const std::weak_ptr<Widget<RenderContext>> &parent) {
  parent_ = parent;
}

template<typename RenderContext>
bool Widget<RenderContext>::HandleInput(const frontend::Input &input) {
  return false;
}

}
