#pragma once

#include <stack>
#include <thread>
#include <stdexcept>
#include <vector>

#include "game_view/IViewFactory.h"
#include "frontend/IFrontendEvents.h"

#include "IScreen.h"

namespace game {

/** Game loop. */
class Game {
 public:
  /**
   * Creates game.
   * @param view_factory View factory creating game views.
   * @param frontend_events Frontend event loop.
   * @param initial_screen Initial screen added to screen stack if it is not equal to `nullptr`. Otherwise screen
   *                       stack remains empty.
   */
  Game(game_view::IViewFactory &view_factory, frontend::IFrontendEvents &frontend_events,
      std::unique_ptr<IScreen> initial_screen);

  /** Runs game. */
  void Run();

 private:
  /** View factory. */
  game_view::IViewFactory &view_factory_;
  /** Frontend events. */
  frontend::IFrontendEvents &frontend_events_;
  /** Stack of screens. Top screen is updated and rendered and it receives all the events. */
  std::stack<std::unique_ptr<IScreen>> screen_stack_;

  /**
   * Handles given action.
   * @param action Action to handle.
   */
  void HandleAction(IScreen::Action action);
  /**
   * Handles given optional action.
   * @param action Optional action to handle.
   */
  void HandleAction(std::optional<IScreen::Action> action);
  /**
   * Pushes given screen to screen stack. Does not initialize screen.
   * @param screen Screen to push.
   */
  void PushScreen(std::unique_ptr<IScreen> screen);
  /** Pops screen from screen stack. Throws `std::runtime_error` if screen stack is empty. */
  void PopScreen();
  /** Pops all screens. */
  void Quit();

  /** Returns true if game loop should be stopped. */
  [[nodiscard]] bool ShouldQuit() const;

};

}
