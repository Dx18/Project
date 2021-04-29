#pragma once

namespace util {

/**
 * Vector holding X and Y values.
 * @tparam T Type of coordinates.
 */
template<typename T>
struct Vector2 {
  /** X coordinate. */
  T x;
  /** Y coordinate. */
  T y;
};

/**
 * Vector holding X, Y and Z values.
 * @tparam T Type of coordinates.
 */
template<typename T>
struct Vector3 {
  /** X coordinate. */
  T x;
  /** Y coordinate. */
  T y;
  /** Z coordinate. */
  T z;
};

}
