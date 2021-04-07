#pragma once

#include <cmath>

#include "config/GameConfig.h"

#include "TechLevel.h"

namespace tech {

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
   */
  Tech(const config::GameConfig &game_config, const config::ConfigSectionStructure &tech_info);

  /** Returns const reference to game config. */
  [[nodiscard]] const config::GameConfig &GameConfig() const;

  /** Returns tech level of firearm weapons. */
  [[nodiscard]] TechLevel FirearmWeaponTechLevel() const;
  /**
   * Sets tech level of firearm weapons.
   * @param new_tech_level Tech level to set.
   */
  void SetFirearmWeaponTechLevel(TechLevel new_tech_level);

  /** Returns tech level of laser weapons. */
  [[nodiscard]] TechLevel LaserWeaponTechLevel() const;
  /**
   * Sets tech level of laser weapons.
   * @param new_tech_level Tech level to set.
   */
  void SetLaserWeaponTechLevel(TechLevel new_tech_level);

  /** Returns tech level of standard armor. */
  [[nodiscard]] TechLevel StandardArmorTechLevel() const;
  /**
   * Sets tech level of standard armor.
   * @param new_tech_level Tech level to set.
   */
  void SetStandardArmorTechLevel(TechLevel new_tech_level);

  /** Returns tech level of composite armor. */
  [[nodiscard]] TechLevel CompositeArmorTechLevel() const;
  /**
   * Sets tech level of composite armor.
   * @param new_tech_level Tech level to set.
   */
  void SetCompositeArmorTechLevel(TechLevel new_tech_level);

  /**
   * Returns max ammo of firearm weapon using current tech level of firearm weapons. Returns 0 if firearm weapons are
   * not researched.
   * @param base_max_ammo Max ammo of particular weapon obtained from game config.
   */
  [[nodiscard]] int FirearmWeaponMaxAmmo(int base_max_ammo) const;
  /**
   * Returns mass of firearm weapon using current tech level of firearm weapons. Returns 0 if firearm weapons are not
   * researched.
   * @param base_mass Mass of particular weapon obtained from game config.
   */
  [[nodiscard]] int FirearmWeaponMass(int base_mass) const;
  /**
   * Returns mass of laser weapon using current tech level of laser weapons. Returns 0 if laser weapons are not
   * researched.
   * @param base_mass Mass of particular weapon obtained from game config.
   */
  [[nodiscard]] int LaserWeaponMass(int base_mass) const;
  /**
   * Returns defence of standard armor using current tech level of standard armor. Returns 0 if standard armor is not
   * researched.
   * @param base_defence Defence of particular kind of standard armor obtained from game config.
   */
  [[nodiscard]] int StandardArmorDefence(int base_defence) const;
  /**
   * Returns mass of standard armor using current tech level of standard armor. Returns 0 if standard armor is not
   * researched.
   * @param base_mass Mass of particular kind of standard armor obtained from game config.
   */
  [[nodiscard]] int StandardArmorMass(int base_mass) const;
  /**
   * Returns defence of composite armor using current tech level of composite armor. Returns 0 if composite armor is
   * not researched.
   * @param base_defence Defence of particular kind of composite armor obtained from game config.
   */
  [[nodiscard]] int CompositeArmorDefence(int base_defence) const;
  /**
   * Returns mass of composite armor using current tech level of composite armor. Returns 0 if composite armor is not
   * researched.
   * @param base_mass Mass of particular kind of composite armor obtained from game config.
   */
  [[nodiscard]] int CompositeArmorMass(int base_mass) const;

 private:
  /** Const reference to game config. */
  const config::GameConfig &game_config_;
  /** Tech level of firearm weapons. */
  TechLevel firearm_weapon_tech_level_;
  /** Tech level of laser weapons. */
  TechLevel laser_weapon_tech_level_;
  /** Tech level of standard armor. */
  TechLevel standard_armor_tech_level_;
  /** Tech level of composite armor. */
  TechLevel composite_armor_tech_level_;

  /**
   * Uses tech level to get the effect of given tech level:
   *   - if `tech_level` is `TechLevel::kNotResearched`, returns 0.0
   *   - if `tech_level` is `TechLevel::kBasic`, returns 1.0
   *   - if `tech_level` is `TechLevel::kAdvanced`, returns value of `advanced_tech_level_effect` stored in game
   *     config.
   * @param tech_level Tech level.
   */
  [[nodiscard]] double TechLevelEffect(TechLevel tech_level) const;

};

}
