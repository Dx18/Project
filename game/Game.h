#pragma once

#include <stack>
#include <thread>
#include <stdexcept>
#include <vector>

#include "frontend/IFrontendEvents.h"
#include "frontend/EventVisitor.h"

#include "IScreen.h"

namespace game {

/**
 * Game loop.
 *
 * @tparam Context Type with associated types `RenderContext` and `Resources` and following methods:
 *                 - `void Render(const widget::Widget<RenderContext> &widget)`;
 *                 - `IFrontendEvents &Events()`.
 */
template<typename Context>
class Game {
 private:
  using IScreenType = IScreen<Context>;
  using IScreenPtr = std::unique_ptr<IScreenType>;
  using Action = typename IScreenType::Action;
  using PushScreenAction = typename IScreenType::PushScreenAction;
  using PopScreenAction = typename IScreenType::PopScreenAction;
  using QuitAction = typename IScreenType::QuitAction;

 public:
  /**
   * Creates game.
   * @param context Game context.
   * @param initial_screen Initial screen added to screen stack if it is not equal to `nullptr`. Otherwise screen
   *                       stack remains empty.
   */
  Game(Context &context, IScreenPtr initial_screen);

  /** Runs game. */
  void Run();

 private:
  /** Context. */
  Context &context_;
  /** Stack of screens. Top screen is updated and rendered and it receives all the events. */
  std::stack<IScreenPtr> screen_stack_;

  /**
   * Handles given action.
   * @param action Action to handle.
   */
  void HandleAction(Action action);
  /**
   * Handles given optional action.
   * @param action Optional action to handle.
   */
  void HandleAction(std::optional<Action> action);
  /**
   * Pushes given screen to screen stack. Does not initialize screen.
   * @param screen Screen to push.
   */
  void PushScreen(IScreenPtr screen);
  /** Pops screen from screen stack. Throws `std::runtime_error` if screen stack is empty. */
  void PopScreen();
  /** Pops all screens. */
  void Quit();

  /** Returns true if game loop should be stopped. */
  [[nodiscard]] bool ShouldQuit() const;

};

template<typename Context>
Game<Context>::Game(Context &context, IScreenPtr initial_screen)
    : context_(context), screen_stack_() {
  if (initial_screen) {
    initial_screen->OnResume();
    PushScreen(std::move(initial_screen));
  }
}

template<typename Context>
void Game<Context>::Run() {
  /** Local implementation of frontend event visitor. */
  class FrontendEventVisitor : public frontend::EventVisitor {
   public:
    /**
     * Creates visitor.
     * @param screen Reference to top screen.
     * @param actions Reference to array of resulting actions.
     */
    FrontendEventVisitor(IScreen<Context> &screen, std::vector<std::optional<Action>> &actions)
        : screen_(screen), actions_(actions) {

    }

    void VisitInputEvent(frontend::InputEvent &event) override {
      actions_.push_back(screen_.OnInput(event));
    }

   private:
    /** Reference to top screen. */
    IScreen<Context> &screen_;
    /** Reference to array of resulting actions. */
    std::vector<std::optional<Action>> &actions_;

  };

  using std::chrono::high_resolution_clock;
  using std::chrono::microseconds;
  using std::chrono::duration_cast;

  auto previous_time = high_resolution_clock::now();
  auto frame_duration = std::chrono::milliseconds(20);
  std::vector<std::optional<Action>> actions;
  while (!ShouldQuit()) {
    auto current_time = high_resolution_clock::now();
    auto target_time = previous_time + frame_duration;

    actions.clear();

    if (current_time < target_time) {
      std::this_thread::sleep_for(target_time - current_time);
    }

    current_time = high_resolution_clock::now();

    IScreenType &screen = *screen_stack_.top();

    frontend::IFrontendEvents &frontend_events = context_.Events();

    FrontendEventVisitor frontend_event_visitor(screen, actions);
    while (std::unique_ptr<frontend::IEvent> event = frontend_events.PollEvent()) {
      event->Accept(frontend_event_visitor);
    }

    microseconds delta = duration_cast<microseconds>(current_time - previous_time);

    actions.push_back(screen.Update(delta));

    widget::Widget<Context> &widget = screen.Render(delta);
    context_.Render(widget);

    for (std::optional<Action> &action : actions) {
      HandleAction(std::move(action));
      if (ShouldQuit()) {
        break;
      }
    }

    previous_time = current_time;
  }
}

template<typename Context>
void Game<Context>::HandleAction(Action action) {
  if (std::holds_alternative<PushScreenAction>(action)) {
    IScreenPtr &screen = std::get<PushScreenAction>(action).new_screen;
    if (screen) {
      PushScreen(std::move(screen));
    }
  } else if (std::holds_alternative<PopScreenAction>(action)) {
    PopScreen();
  } else if (std::holds_alternative<QuitAction>(action)) {
    Quit();
  }
}

template<typename Context>
void Game<Context>::HandleAction(std::optional<Action> action) {
  if (action.has_value()) {
    HandleAction(std::move(action.value()));
  }
}

template<typename Context>
void Game<Context>::PushScreen(IScreenPtr screen) {
  if (!screen_stack_.empty()) {
    screen_stack_.top()->OnPause();
  }
  screen_stack_.push(std::move(screen));
  screen_stack_.top()->OnResume();
}

template<typename Context>
void Game<Context>::PopScreen() {
  if (screen_stack_.empty()) {
    throw std::runtime_error("cannot pop screen because screen stack is empty");
  }

  screen_stack_.top()->OnPause();
  screen_stack_.pop();
  if (!screen_stack_.empty()) {
    screen_stack_.top()->OnResume();
  }
}

template<typename Context>
void Game<Context>::Quit() {
  while (!screen_stack_.empty()) {
    PopScreen();
  }
}

template<typename Context>
bool Game<Context>::ShouldQuit() const {
  return screen_stack_.empty();
}

}
