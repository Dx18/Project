#pragma once

#include <array>

namespace frontend::terminal {

/** Color of character. */
enum Color {
  /** Black. */
  kBlack = 0,
  /** Red. */
  kRed = 1,
  /** Green. */
  kGreen = 2,
  /** Yellow. */
  kYellow = 3,
  /** Blue. */
  kBlue = 4,
  /** Magenta. */
  kMagenta = 5,
  /** Cyan. */
  kCyan = 6,
  /** White. */
  kWhite = 7
};

/** Array of colors for iteration. */
static const std::array<Color, 8> kColors = {
    Color::kBlack,
    Color::kRed,
    Color::kGreen,
    Color::kYellow,
    Color::kBlue,
    Color::kMagenta,
    Color::kCyan,
    Color::kWhite,
};

}
