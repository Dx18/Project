#pragma once

#include <cmath>

namespace util::math {

/**
 * If `min` <= `value` <= `max`, returns `value`. If `value` < `min`, returns `min`. Otherwise returns `max`. In other
 * words, makes `value` fit in range [`min`; `max`]. Important note: result is undefined if `min` > `max`.
 * @tparam T Type of arguments.
 * @param value Value.
 * @param min Min bound for value.
 * @param max Max bound for value.
 */
template<typename T>
const T &clamp(const T &value, const T &min, const T &max) {
  return std::min(std::max(value, min), max);
}

/**
 * If `min` <= `value` <= `max`, returns `value`. If `value` < `min`, returns `min`. Otherwise returns `max`. In other
 * words, makes `value` fit in range [`min`; `max`]. Uses `comp` for comparing values. Important note: result is
 * undefined if `min` > `max`.
 * @tparam T Type of arguments.
 * @param value Value.
 * @param min Min bound for value.
 * @param max Max bound for value.
 * @param comp Comparator.
 */
template<typename T, typename Compare>
const T &clamp(const T &value, const T &min, const T &max, Compare comp) {
  return std::min(std::max(value, min, comp), comp);
}

}
