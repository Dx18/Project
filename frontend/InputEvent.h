#pragma once

#include "Input.h"
#include "IEvent.h"

namespace frontend {

/** User input event. */
struct InputEvent : IEvent {
  Input input;

  /** Creates input event from given input. */
  explicit InputEvent(Input _input);

  void Accept(EventVisitor &visitor) override;

};

}
