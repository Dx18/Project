#pragma once

#include "Color.h"

namespace frontend::terminal {

/** Pair of colors: foreground and background. */
struct ColorPair {
  /** Foreground color. */
  Color foreground;
  /** Background color. */
  Color background;

  /**
   * Creates color pair from given foreground and background colors.
   * @param _foreground Foreground color.
   * @param _background Background color.
   */
  ColorPair(Color _foreground, Color _background);

};

}
