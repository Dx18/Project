#include "Game.h"

namespace game {

Game::Game(game_view::IViewFactory &view_factory,
           frontend::IFrontendEvents &frontend_events,
           std::unique_ptr<IScreen> initial_screen)
    : view_factory_(view_factory),
      frontend_events_(frontend_events),
      screen_stack_() {
  if (initial_screen) {
    initial_screen->Initialize(view_factory_);
    PushScreen(std::move(initial_screen));
  }
}

void Game::Run() {
  using std::chrono::high_resolution_clock;
  using std::chrono::microseconds;
  using std::chrono::duration_cast;

  auto previous_time = high_resolution_clock::now();
  auto frame_duration = std::chrono::milliseconds(20);
  while (!ShouldQuit()) {
    auto current_time = high_resolution_clock::now();
    auto target_time = previous_time + frame_duration;

    if (current_time < target_time) {
      std::this_thread::sleep_for(target_time - current_time);
    }

    current_time = high_resolution_clock::now();

    IScreen &screen = *screen_stack_.top();

    while (std::unique_ptr<frontend::IEvent> event = frontend_events_.PollEvent()) {
      if (auto input_event = dynamic_cast<const frontend::InputEvent *>(event.get())) {
        HandleAction(screen.OnInput(*input_event));
      }

      if (ShouldQuit()) {
        break;
      }
    }

    if (ShouldQuit()) {
      break;
    }

    microseconds delta = duration_cast<microseconds>(current_time - previous_time);

    HandleAction(screen.Update(delta));
    if (ShouldQuit()) {
      break;
    }

    HandleAction(screen.Render(delta));
    if (ShouldQuit()) {
      break;
    }

    previous_time = current_time;
  }
}

void Game::HandleAction(IScreen::Action action) {
  if (std::holds_alternative<IScreen::PushScreenAction>(action)) {
    std::unique_ptr<IScreen> &screen = std::get<IScreen::PushScreenAction>(action).new_screen;
    if (screen) {
      PushScreen(std::move(screen));
    }
  } else if (std::holds_alternative<IScreen::PopScreenAction>(action)) {
    PopScreen();
  } else if (std::holds_alternative<IScreen::QuitAction>(action)) {
    Quit();
  }
}

void Game::HandleAction(std::optional<IScreen::Action> action) {
  if (action.has_value()) {
    HandleAction(std::move(action.value()));
  }
}

void Game::PushScreen(std::unique_ptr<IScreen> screen) {
  if (!screen_stack_.empty()) {
    screen_stack_.top()->OnPause();
  }
  screen_stack_.push(std::move(screen));
  screen_stack_.top()->OnResume();
}

void Game::PopScreen() {
  if (screen_stack_.empty()) {
    throw std::runtime_error("cannot pop screen because screen stack is empty");
  }

  screen_stack_.top()->OnPause();
  screen_stack_.pop();
  if (!screen_stack_.empty()) {
    screen_stack_.top()->OnResume();
  }
}

void Game::Quit() {
  while (!screen_stack_.empty()) {
    PopScreen();
  }
}

bool Game::ShouldQuit() const {
  return screen_stack_.empty();
}

}
