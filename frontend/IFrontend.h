#pragma once

#include <memory>

#include "IEvent.h"

namespace frontend {

/** Frontend: used to get events such as user input. */
class IFrontend {
 public:
  virtual ~IFrontend() = 0;

  /** Polls event and returns pointer to it. If there is no event, returns `nullptr`. */
  virtual std::unique_ptr<IEvent> PollEvent() = 0;

};

}
