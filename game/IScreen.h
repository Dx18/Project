#pragma once

#include <optional>
#include <chrono>
#include <memory>

#include "frontend/InputEvent.h"
#include "game_view/IViewFactory.h"

namespace game {

/**
 * Game screen with defined lifecycle.
 *
 * Lifecycle:
 * - Initialize: post-constructor initialization; called once when screen is just created;
 * - OnResume: called after:
 *   - post-constructor initialization;
 *   - popping other screen from screen stack;
 * - Update: called when screen needs to be updated;
 * - Render: called when screen needs to be rendered;
 * - OnPause: called before:
 *   - popping current screen from screen stack;
 *   - pushing other screen to screen stack.
 *
 * Other events:
 * - OnInput: character or key input is received.
 */
class IScreen {
 public:
  /** Request to push given screen to screen stack. */
  struct PushScreenAction {
    /** New screen. */
    std::unique_ptr<game::IScreen> new_screen;

    /**
     * Creates push screen action.
     * @param new_screen New screen.
     */
    explicit PushScreenAction(std::unique_ptr<game::IScreen> new_screen);

  };

  /** Request to pop current screen from screen stack. */
  struct PopScreenAction {};

  /** Request to quit. */
  struct QuitAction {};

  /** Action which can be requested by screen. */
  using Action = std::variant<PushScreenAction, PopScreenAction, QuitAction>;

  virtual ~IScreen() = 0;

  /** Post-constructor initialization. */
  virtual void Initialize(game_view::IViewFactory &view_factory) = 0;
  /**
   * Called when screen needs to be updated. May return game action.
   * @param delta Time passed from previous frame in seconds.
   */
  virtual std::optional<Action> Update(std::chrono::microseconds delta) = 0;
  /**
   * Called when screen needs to be rendered. May return game action.
   * @param delta Time passed from previous frame in seconds.
   */
  virtual std::optional<Action> Render(std::chrono::microseconds delta) = 0;
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

}
