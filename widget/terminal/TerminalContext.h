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

/** Terminal game context. */
class TerminalContext {
 public:
  /** Context used for rendering widgets. */
  using RenderContext = IRenderSurfaceWrite;

  /**
   * Creates terminal context.
   * @param input Terminal input.
   * @param renderer Terminal renderer.
   */
  TerminalContext(ITerminalInput &input, ITerminalRenderer &renderer);

  /** Returns reference to terminal events. */
  TerminalEvents &Events();
  /**
   * Renders given widget.
   * @param widget Widget to render.
   */
  void Render(widget::Widget<IRenderSurfaceWrite> &widget);

 private:
  /** Rendering surface. */
  RenderSurfaceBase surface_;
  /** Terminal events. */
  TerminalEvents events_;
  /** Terminal renderer. */
  ITerminalRenderer &renderer_;

};

}
