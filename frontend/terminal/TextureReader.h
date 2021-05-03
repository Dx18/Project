#pragma once

#include "RenderSurfaceBase.h"

namespace frontend::terminal {

/**
 * Texture reader.
 *
 * # Format
 *
 * Format of texture:
 *
 * ```
 * <height> <width>
 * <`height` lines with `column` characters, optionally ending with ';' (texture characters)>
 * <`height` lines with `column` digits from 0 to 7 (inclusive) (foreground color for each character)>
 * <`height` lines with `column` digits from 0 to 7 (inclusive) (background color for each character)>
 * ```
 *
 * Colors represented with digit, according to number in `Color` enum.
 *
 * # Example
 *
 * ```
 * 4 4
 * +--+;
 * |==|;
 * |==|;
 * +--+;
 * 1111
 * 1331
 * 1331
 * 1111
 * 3333
 * 3003
 * 3003
 * 3333
 * ```
 */
class TextureReader {
 public:
  /**
   * Reads texture. Throws `std::runtime_error` if error is occurred: cannot read from input or input format is not
   * valid.
   * @param in Input stream.
   */
  RenderSurfaceBase ReadTexture(std::istream &in) const;

};

}
