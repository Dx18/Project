#include "TerminalEvents.h"

namespace frontend::terminal {

TerminalEvents::TerminalEvents(ITerminalInput &input)
    : input_(input) {

}

std::unique_ptr<IEvent> TerminalEvents::PollEvent() {
  std::optional<Input> current_input = input_.PollInput();
  if (current_input.has_value()) {
    return std::make_unique<InputEvent>(current_input.value());
  }

  return nullptr;
}

}
