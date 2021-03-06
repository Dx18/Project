#pragma once

#include <optional>
#include <chrono>
#include <memory>

#include "frontend/InputEvent.h"
#include "widget/Widget.h"

namespace game {

/**
 * Game screen with defined lifecycle.
 *
 * Lifecycle:
 * - OnResume: called after:
 *   - constructing;
 *   - popping other screen from screen stack;
 * - Update: called when screen needs to be updated;
 * - Render: called when screen needs to be rendered;
 * - OnPause: called before:
 *   - popping current screen from screen stack;
 *   - pushing other screen to screen stack.
 *
 * Other events:
 * - OnInput: character or key input is received.
 *
 * @tparam Context Type with following associated types: `Context::RenderContext` (used to render widget),
 *                 `Context::ResourcesContext` (resources associated with context).
 */
template<typename Context>
class IScreen {
 public:
  /** Request to push given screen to screen stack. */
  struct PushScreenAction {
    /** New screen. */
    std::unique_ptr<game::IScreen<Context>> new_screen;

    /**
     * Creates push screen action.
     * @param new_screen New screen.
     */
    explicit PushScreenAction(std::unique_ptr<game::IScreen<Context>> new_screen);

  };

  /** Request to pop current screen from screen stack. */
  struct PopScreenAction {};

  /** Request to quit. */
  struct QuitAction {};

  /** Action which can be requested by screen. */
  using Action = std::variant<PushScreenAction, PopScreenAction, QuitAction>;

  virtual ~IScreen() = 0;

  /**
   * Called when screen needs to be updated. May return game action.
   * @param delta Time passed from previous frame in seconds.
   */
  virtual std::optional<Action> Update(std::chrono::microseconds delta) = 0;
  /**
   * Called when screen needs to be rendered. May return game action.
   * @param delta Time passed from previous frame in seconds.
   */
  virtual widget::Widget<Context> &Render(std::chrono::microseconds delta) = 0;
  /**
   * Called after:
   * - post-constructor initialization;
   * - popping other screen from screen stack.
   */
  virtual std::optional<Action> OnResume();
  /**
   * Called before:
   * - popping current screen from screen stack;
   * - pushing other screen to screen stack.
   */
  virtual std::optional<Action> OnPause();
  /**
   * Called when character or key input is received.
   * @param event Event info.
   */
  virtual std::optional<Action> OnInput(const frontend::InputEvent &event);

};

template<typename Context>
IScreen<Context>::PushScreenAction::PushScreenAction(std::unique_ptr<game::IScreen<Context>> _new_screen)
    : new_screen(std::move(_new_screen)) {

}

template<typename Context>
IScreen<Context>::~IScreen() = default;

template<typename Context>
std::optional<typename IScreen<Context>::Action> IScreen<Context>::OnResume() {
  return {};
}

template<typename Context>
std::optional<typename IScreen<Context>::Action> IScreen<Context>::OnPause() {
  return {};
}

template<typename Context>
std::optional<typename IScreen<Context>::Action> IScreen<Context>::OnInput(const frontend::InputEvent &event) {
  return {};
}

}
