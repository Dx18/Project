#pragma once

#include <ostream>

#include "Vector.h"

namespace util {

/**
 * 2D rectangle represented with coordinates and size.
 * @tparam T Type of coordinates and dimensions.
 */
template<typename T>
struct Rectangle {
  /** X coordinate. */
  T x;
  /** Y coordinate. */
  T y;
  /** Width. */
  T width;
  /** Height. */
  T height;

  /**
   * Returns true if current rectangle contains given rectangle.
   * @param rectangle Rectangle to check.
   */
  bool ContainsRectangle(const Rectangle<T> &rectangle) const;
  /**
   * Returns true if current rectangle contains given point. Note that rectangle contains only points with coordinates
   * (x', y'), such as `x` <= `x'` < `x` + `width` and `y` <= `y'` < `y` + `height`.
   * @param point Point to check.
   */
  bool ContainsPoint(const Vector2<T> &point) const;

};

template<typename T>
bool Rectangle<T>::ContainsRectangle(const Rectangle<T> &rectangle) const {
  return x >= rectangle.x && x + width <= rectangle.x + rectangle.width
      && y >= rectangle.y && y + height <= rectangle.y + rectangle.height;
}

template<typename T>
bool Rectangle<T>::ContainsPoint(const Vector2<T> &point) const {
  return point.x >= x && point.x < x + width
      && point.y >= y && point.y < y + height;
}

/**
 * Prints rectangle to output stream. Format of output: "{x: `x`, y: `y`, width: `width`, height: `height`}".
 * @tparam T Type of coordinates and dimensions in rectangle.
 * @param out Output stream.
 * @param rectangle Rectangle to print.
 */
template<typename T>
std::ostream &operator<<(std::ostream &out, const Rectangle<T> &rectangle) {
  return out << "{x: " << rectangle.x << ", y: " << rectangle.y
             << ", width: " << rectangle.width << ", height: " << rectangle.height << "}";
}

}
