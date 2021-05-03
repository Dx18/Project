#pragma once

#include "frontend/IFrontendEvents.h"
#include "frontend/InputEvent.h"

#include "ITerminalInput.h"

namespace frontend::terminal {

/** Terminal event loop. */
class TerminalEvents : public IFrontendEvents {
 public:
  /** Creates terminal events reading input from given input. */
  explicit TerminalEvents(ITerminalInput &input);

  std::unique_ptr<IEvent> PollEvent() override;

 private:
  /** Terminal input. */
  ITerminalInput &input_;

};

}
