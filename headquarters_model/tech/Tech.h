#pragma once

#include <cmath>

#include "config/GameConfig.h"
#include "headquarters_model/Resources.h"
#include "object_database/WeaponTechInfo.h"
#include "object_database/ArmorTechInfo.h"

#include "TechLevel.h"
#include "ResearchResult.h"

namespace headquarters_model::tech {

using namespace headquarters_model;
using namespace object_database;

/** Technologies currently researched. */
class Tech {
 public:
  /**
   * Creates information about technologies currently researched.
   *
   * Tech level is represented as integer:
   *   - 0 is `TechLevel::kNotResearched`
   *   - 1 is `TechLevel::kBasic`
   *   - 2 is `TechLevel::kAdvanced`
   * @param game_config Const reference to game config.
   * @param tech_info Tech info: config section structure containing the following fields:
   *                    - firearm_weapon_tech_level
   *                    - laser_weapon_tech_level
   *                    - standard_armor_tech_level
   *                    - composite_armor_tech_level
   * @param resources Reference to resources.
   */
  Tech(const config::GameConfig &game_config, const config::ConfigSectionStructure &tech_info, Resources &resources);

  /**
   * Returns max ammo of weapons of given weapon type if exists. Uses current tech level. Returns 0 if technology is
   * not researched
   * @param type Type of weapon.
   */
  [[nodiscard]] std::optional<int> WeaponMaxAmmo(WeaponType type) const;
  /**
   * Returns mass of weapons of given weapon type. Uses current tech level. Returns 0 if technology is not researched
   * @param type Type of weapon.
   */
  [[nodiscard]] int WeaponMass(WeaponType type) const;
  /**
   * Returns defence of armor of given armor type. Uses current tech level. Returns 0 if technology is not researched
   * @param type Type of armor.
   */
  [[nodiscard]] int ArmorDefence(ArmorType type) const;
  /**
   * Returns mass of armor of given armor type. Uses current tech level. Returns 0 if technology is not researched
   * @param type Type of armor.
   */
  [[nodiscard]] int ArmorMass(ArmorType type) const;

  /**
   * Returns current tech level of given weapon tech type.
   * @param tech_type Tech type of weapon.
   */
  [[nodiscard]] TechLevel WeaponTechLevel(WeaponTechType tech_type) const;
  /**
   * Returns current tech level of given armor tech type.
   * @param tech_type Tech type of armor.
   */
  [[nodiscard]] TechLevel ArmorTechLevel(ArmorTechType tech_type) const;
  /**
   * Tries to increase weapon tech level. Returned result:
   * - `ResearchResult::kResearched` if research is successfully performed.
   * - `ResearchResult::kAlreadyMaxLevel` if current tech level is already max possible.
   * - `ResearchResult::kNotEnoughResources` if there is not enough resources for research.
   * @param tech_type Tech type of weapon.
   */
  ResearchResult ResearchWeapon(WeaponTechType tech_type);
  /**
   * Tries to increase armor tech level. Returned result:
   * - `ResearchResult::kResearched` if research is successfully performed.
   * - `ResearchResult::kAlreadyMaxLevel` if current tech level is already max possible.
   * - `ResearchResult::kNotEnoughResources` if there is not enough resources for research.
   * @param tech_type Tech type of armor.
   */
  ResearchResult ResearchArmor(ArmorTechType tech_type);

 private:
  /** Const reference to game config. */
  const config::GameConfig &game_config_;
  /** Tech levels of weapons. */
  std::array<TechLevel, kWeaponTechInfo.size()> weapon_tech_level_;
  /** Tech levels of armor. */
  std::array<TechLevel, kArmorTechInfo.size()> armor_tech_level_;
  /** Reference to resources. */
  Resources &resources_;

  /**
   * Uses tech level to get the effect of given tech level:
   *   - if `tech_level` is `TechLevel::kNotResearched`, returns 0.0
   *   - if `tech_level` is `TechLevel::kBasic`, returns 1.0
   *   - if `tech_level` is `TechLevel::kAdvanced`, returns value of `advanced_tech_level_effect` stored in game
   *     config.
   * @param tech_level Tech level.
   */
  [[nodiscard]] double TechLevelEffect(TechLevel tech_level) const;

  /**
   * Calculates generic characteristic with value proportional to tech level using its base value and tech level.
   * Returns 0 if given tech level is `TechLevel::kNotResearched`.
   * @param tech_level Tech level.
   * @param base_value Base value of characteristic.
   */
  [[nodiscard]] int CalculateIncreasing(TechLevel tech_level, int base_value) const;
  /**
   * Calculates generic characteristic with value not proportional to tech level using its base value and tech level.
   * Returns 0 if given tech level is `TechLevel::kNotResearched`.
   * @param tech_level Tech level.
   * @param base_value Base value of characteristic.
   */
  [[nodiscard]] int CalculateDecreasing(TechLevel tech_level, int base_value) const;

};

}
