#pragma once

#include <array>

#include "config/ConfigSectionStructure.h"
#include "object_database/WeaponInfo.h"
#include "object_database/ArmorInfo.h"
#include "headquarters_model/Resources.h"

#include "BuildResult.h"

namespace headquarters_model::armory {

using namespace object_database;

/** Armory: weapon and armor storage. */
class Armory {
 public:
  /**
   * Creates armory from given data.
   * @param armory_info Information about armory.
   */
  explicit Armory(const config::ConfigSectionStructure &armory_info);

  /**
   * Returns number of weapons of certain type.
   * @param type Type of weapon.
   */
  [[nodiscard]] size_t WeaponCount(WeaponType type) const;
  /**
   * Tries to build weapon. Returned result:
   * - `BuildResult::kBuild` if building was successful.
   * - `BuildResult::kNotEnoughResources` if there is not enough resources for building.
   * @param type Type of weapon to build.
   * @param resources Reference to resources.
   */
  BuildResult BuildWeapon(WeaponType type, Resources &resources);
  /**
   * Returns number of armor of certain type.
   * @param type Type of armor.
   */
  [[nodiscard]] size_t ArmorCount(ArmorType type) const;
  /**
   * Tries to build armor. Returned result:
   * - `BuildResult::kBuild` if building was successful.
   * - `BuildResult::kNotEnoughResources` if there is not enough resources for building.
   * @param type Type of armor to build.
   * @param resources Reference to resources.
   */
  BuildResult BuildArmor(ArmorType type, Resources &resources);

 private:
  /** Current number of each type of weapon. */
  std::array<size_t, kWeaponInfo.size()> weapon_count_;
  /** Current number of each type of armor. */
  std::array<size_t, kArmorInfo.size()> armor_count_;

};

}
