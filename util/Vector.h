#pragma once

#include <ostream>

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

/**
 * Prints 2D vector to output stream. Format of output: "{x: `x`, y: `y`}".
 * @tparam T Type of coordinates.
 * @param out Output stream.
 * @param vector Vector to print.
 */
template<typename T>
std::ostream &operator<<(std::ostream &out, const Vector2<T> &vector) {
  return out << "{x: " << vector.x << ", y: " << vector.y << "}";
}

/**
 * Prints 3D vector to output stream. Format of output: "{x: `x`, y: `y`, z: `z`}".
 * @tparam T Type of coordinates.
 * @param out Output stream.
 * @param vector Vector to print.
 */
template<typename T>
std::ostream &operator<<(std::ostream &out, const Vector3<T> &vector) {
  return out << "{x: " << vector.x << ", y: " << vector.y << ", z: " << vector.z << "}";
}

}
