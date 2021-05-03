#pragma once

#include "object_database/WeaponInfo.h"
#include "object_database/ArmorInfo.h"

#include "ConfigSectionStructure.h"

namespace config {

using namespace object_database;

/** Game process config. */
class GameConfig {
 public:
  /**
   * Creates game config from given structure.
   * @param section Structure of game config.
   */
  explicit GameConfig(const ConfigSectionStructure &section);

  /**
   * Returns max ammo of weapon of given type. If it does not exist returns empty value.
   * @param type Type of weapon.
   */
  [[nodiscard]] std::optional<int> WeaponMaxAmmo(WeaponType type) const;
  /**
   * Returns mass of weapon of given type.
   * @param type Type of weapon
   */
  [[nodiscard]] int WeaponMass(WeaponType type) const;
  /**
   * Returns defence of armor of given type.
   * @param type Type of armor.
   */
  [[nodiscard]] int ArmorDefence(ArmorType type) const;
  /**
   * Returns mass of armor of given type.
   * @param type Type of armor.
   */
  [[nodiscard]] int ArmorMass(ArmorType type) const;

  /** Returns effect of advanced tech level. Base value is multiplied or divided by the effect to get final value. */
  [[nodiscard]] double AdvancedTechLevelEffect() const;

  /** Default number of soldiers/drones in squad. */
  [[nodiscard]] int SquadSize() const;

 private:
  /** Array with weapon max ammo. */
  std::array<std::optional<int>, kWeaponInfo.size()> weapon_max_ammo_;
  /** Array with weapon mass. */
  std::array<int, kWeaponInfo.size()> weapon_mass_;
  /** Array with armor defence. */
  std::array<int, kArmorInfo.size()> armor_defence_;
  /** Array with armor mass. */
  std::array<int, kArmorInfo.size()> armor_mass_;
  /** Effect of advanced tech level. Base value is multiplied or divided by the effect to get final value. */
  double advanced_tech_level_effect_;
  /** Default number of soldiers/drones in squad. */
  int squad_size_;

};

}
