#pragma once

#include "EventVisitor.h"

namespace frontend {

/** Event happened on frontend. */
class IEvent {
 public:
  virtual ~IEvent() = 0;

  /**
   * Accepts visitor.
   * @param visitor Visitor to accept.
   */
  virtual void Accept(EventVisitor &visitor) = 0;

};

}
