#include "IScreen.h"

namespace game {

IScreen::PushScreenAction::PushScreenAction(std::unique_ptr<game::IScreen> _new_screen)
    : new_screen(std::move(_new_screen)) {

}

IScreen::~IScreen() = default;

std::optional<IScreen::Action> IScreen::OnResume() {
  return {};
}

std::optional<IScreen::Action> IScreen::OnPause() {
  return {};
}

std::optional<IScreen::Action> IScreen::OnInput(const frontend::InputEvent &event) {
  return {};
}

}
