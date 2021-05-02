#include "InputEvent.h"

namespace frontend {

InputEvent::InputEvent(Input _input)
    : input(_input) {

}

void InputEvent::Accept(EventVisitor &visitor) {
  visitor.VisitInputEvent(*this);
}

}
