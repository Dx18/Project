#pragma once

namespace headquarters_model::tech {

/** Level of technology available. */
enum TechLevel {
  /** Technology is not available. */
  kNotResearched = 0,
  /** Basic level of technology is researched. */
  kBasic = 1,
  /** Advanced level of technology is researched. */
  kAdvanced = 2
};

/**
 * Creates tech level from given integer. If given integer is not valid (value is not equal to
 * `TechLevel::kNotResearched`, `TechLevel::kBasic` and `TechLevel::kAdvanced`), then function throws
 * `std::runtime_error`.
 * @param value Value to construct tech level from.
 */
TechLevel tech_level_from_int(int value);

}
