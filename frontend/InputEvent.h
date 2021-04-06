#pragma once

#include "Input.h"
#include "IEvent.h"

namespace frontend {

/** User input event. */
struct CharInputEvent : IEvent {
  Input input;
};

}
