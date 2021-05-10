#include "widget/game/WorldViewWidget.h"

#include "../WorldRenderer.h"
#include "../TerminalContext.h"

namespace widget::game {

using namespace frontend::terminal;

template<>
util::Vector2<size_t> WorldViewWidget<widget::terminal::TerminalContext>::MinSize(TerminalResources &resources) const {
  return {1, 1};
}

template<>
void WorldViewWidget<widget::terminal::TerminalContext>::Render(IRenderSurfaceWrite &context,
                                                                TerminalResources &resources) {
  widget::terminal::WorldRenderer renderer;
  renderer.Render(
      *world_, camera_position_, pointed_tile_highlighted_, navigation_tiles_, selected_unit_,
      context, resources
  );
}

}
