#pragma once

#include <optional>

#include "frontend/Input.h"

namespace frontend::terminal {

using namespace frontend;

/** Terminal input. */
class ITerminalInput {
 public:
  virtual ~ITerminalInput() = 0;

  /** Polls terminal input. Does not block. */
  virtual std::optional<Input> PollInput() = 0;

};

}
