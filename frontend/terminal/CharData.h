#pragma once

#include "ColorPair.h"

namespace frontend::terminal {

/** Drawable character data. */
struct CharData {
  /** Character to draw. */
  char ch;
  /** Foreground/background color. */
  ColorPair color;

  /**
   * Creates character data from given character and color.
   * @param _ch Character.
   * @param _color Color.
   */
  CharData(char _ch, ColorPair _color);

};

}
