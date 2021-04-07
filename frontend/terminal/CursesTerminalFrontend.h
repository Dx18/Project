#pragma once

#include <unordered_map>
#include <ncurses.h>

#include "util/Math.h"

#include "ITerminalRenderer.h"
#include "ITerminalInput.h"

namespace frontend::terminal {

/** NCurses frontend. */
class CursesTerminalFrontend : public ITerminalRenderer, public ITerminalInput {
 public:
  /** Creates frontend, initializes main window. */
  CursesTerminalFrontend();
  /** Destroys main window. */
  ~CursesTerminalFrontend() noexcept override;

  [[nodiscard]] util::Vector2<size_t> Size() const override;
  void SetCursorState(bool enabled) override;
  void SetCursorPosition(const util::Vector2<size_t> &position) override;
  void BeginRender() override;
  void Render(const IRenderSurfaceRead &surface, const util::Vector2<ssize_t> &position) override;
  void EndRender() override;
  std::optional<Input> PollInput() override;

 private:
  /** Map from `ncurses` key codes to enum `Key`. */
  std::unordered_map<int, Key> key_map_;
  /** Map from enum `Color` to `ncurses` color codes. */
  std::unordered_map<Color, int> color_map_;

  /** Initializes key map. */
  void CreateKeyMap();
  /** Initializes color map. */
  void CreateColorMap();

  /** Returns index of given color pair stored in `ncurses`. */
  static size_t ColorPairIndex(ColorPair color_pair);

};

}
