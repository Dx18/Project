#include "ColorPair.h"

namespace frontend::terminal {

ColorPair::ColorPair(Color _foreground, Color _background)
    : foreground(_foreground), background(_background) {

}

ColorPair ColorPair::Inverted() const {
  Color new_foreground = background;
  Color new_background = foreground;
  return ColorPair(new_foreground, new_background);
}

}
