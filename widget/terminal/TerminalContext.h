#pragma once

#include "frontend/terminal/IRenderSurfaceWrite.h"
#include "frontend/terminal/RenderSurfaceBase.h"
#include "frontend/terminal/TerminalEvents.h"
#include "frontend/terminal/ITerminalInput.h"
#include "frontend/terminal/ITerminalRenderer.h"
#include "widget/Widget.h"

namespace widget::terminal {

using namespace frontend::terminal;
using namespace widget;

class TerminalContext {
 public:
  using RenderContext = IRenderSurfaceWrite;

  TerminalContext(ITerminalInput &input, ITerminalRenderer &renderer);

  TerminalEvents &Events();
  void Render(widget::Widget<IRenderSurfaceWrite> &widget);

 private:
  RenderSurfaceBase surface_;
  TerminalEvents events_;
  ITerminalRenderer &renderer_;

};

}
