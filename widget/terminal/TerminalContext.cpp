#include "TerminalContext.h"

namespace widget::terminal {

TerminalContext::TerminalContext(ITerminalInput &input, ITerminalRenderer &renderer, const std::string &resources_path)
    : events_(input), resources_(resources_path), renderer_(renderer), surface_() {

}

TerminalEvents &TerminalContext::Events() {
  return events_;
}

void TerminalContext::Render(widget::Widget<TerminalContext> &widget) {
  using namespace frontend::terminal;

  surface_.ResizeClear(renderer_.Size(),
                       CharData(
                           ' ',
                           ColorPair(Color::kWhite, Color::kBlack)
                       ));

  widget.Render(surface_, resources_);
  renderer_.Render(surface_, {0, 0});
}

}
