#pragma once

#include "frontend/terminal/IRenderSurfaceWrite.h"
#include "frontend/terminal/RenderSurfaceBase.h"
#include "frontend/terminal/TerminalEvents.h"
#include "frontend/terminal/ITerminalInput.h"
#include "frontend/terminal/ITerminalRenderer.h"
#include "frontend/terminal/TerminalResources.h"
#include "widget/Widget.h"

namespace widget::terminal {

using namespace frontend::terminal;
using namespace widget;

/** Terminal game context. */
class TerminalContext {
 public:
  /** Context used for rendering widgets. */
  using RenderContext = IRenderSurfaceWrite;
  /** Resources. */
  using Resources = TerminalResources;

  /**
   * Creates terminal context.
   * @param input Terminal input.
   * @param renderer Terminal renderer.
   */
  TerminalContext(ITerminalInput &input, ITerminalRenderer &renderer, const std::string &resources_path);

  /** Returns reference to terminal events. */
  TerminalEvents &Events();
  /**
   * Renders given widget.
   * @param widget Widget to render.
   */
  void Render(widget::Widget<TerminalContext> &widget);

 private:
  /** Rendering surface. */
  RenderSurfaceBase surface_;
  /** Resources. */
  TerminalResources resources_;
  /** Terminal events. */
  TerminalEvents events_;
  /** Terminal renderer. */
  ITerminalRenderer &renderer_;

};

}
