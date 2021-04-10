#include "TerminalContext.h"

namespace widget::terminal {

TerminalContext::TerminalContext(ITerminalInput &input, ITerminalRenderer &renderer)
    : events_(input), renderer_(renderer), surface_() {

}

TerminalEvents &TerminalContext::Events() {
  return events_;
}

void TerminalContext::Render(widget::Widget<IRenderSurfaceWrite> &widget) {
  using namespace frontend::terminal;

  surface_.ResizeClear(renderer_.Size(),
                       CharData(
                           ' ',
                           ColorPair(Color::kWhite, Color::kBlack)
                       ));

  widget.Render(surface_);
  renderer_.Render(surface_, {0, 0});
}

}
