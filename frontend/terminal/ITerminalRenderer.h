#pragma once

#include "util/Vector.h"

#include "IRenderSurfaceRead.h"

namespace frontend::terminal {

/** Terminal renderer. */
class ITerminalRenderer {
 public:
  virtual ~ITerminalRenderer() = 0;

  /** Returns current size of terminal. */
  [[nodiscard]] virtual util::Vector2<size_t> Size() const = 0;
  /**
   * Sets state of cursor.
   * @param enabled True if cursor should be enabled.
   */
  virtual void SetCursorState(bool enabled) = 0;
  /**
   * Sets position of cursor.
   * @param position Position to set.
   */
  virtual void SetCursorPosition(const util::Vector2<size_t> &position) = 0;
  /** Begins rendering. */
  virtual void BeginRender() = 0;
  /**
   * Renders given surface. Draws only visible part of surface, does not throw exceptions if some parts of surface
   * are out of terminal bounds.
   * @param surface Surface to render.
   * @param position Position of top-left corner of surface to draw.
   */
  virtual void Render(const IRenderSurfaceRead &surface, const util::Vector2<ssize_t> &position) = 0;
  /** Ends rendering. */
  virtual void EndRender() = 0;

};

}
