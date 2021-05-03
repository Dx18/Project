#pragma once

namespace frontend {

class InputEvent;

/** Visitor for frontend events. */
class EventVisitor {
 public:
  /** Visits input event. */
  virtual void VisitInputEvent(InputEvent &event);

};

}
