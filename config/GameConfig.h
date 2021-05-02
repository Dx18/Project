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
   * Returns base damage of weapon of given type.
   * @param typeType of weapon.
   */
  [[nodiscard]] int WeaponBaseDamage(WeaponType type) const;
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

  /** Number of parts world map divided into by each dimension during generation. */
  [[nodiscard]] int WorldMapSubdivision() const;
  /** Size of world map part. */
  [[nodiscard]] int WorldMapPartSize() const;
  /** Max number of houses on map. */
  [[nodiscard]] int WorldMapMaxHouseCount() const;

  /** Min size of enemy squad. */
  [[nodiscard]] int MinEnemySquadSize() const;
  /** Min difficulty when enemies begin to use laser weapons. */
  [[nodiscard]] double LaserWeaponDifficultyThreshold() const;
  /** Min difficulty when enemies begin to wear composite armor. */
  [[nodiscard]] double CompositeArmorDifficultyThreshold() const;
  /** Probability of enemy soldier having secondary weapon - pistol. */
  [[nodiscard]] double EnemySecondaryWeaponProbability() const;

  /** Base health of soldier. */
  [[nodiscard]] int SoldierBaseHealth() const;
  /** Base health of drone. */
  [[nodiscard]] int DroneBaseHealth() const;

  /** Max limit of distance soldier can travel at one step. */
  [[nodiscard]] int MaxSoldierTravelDistanceLimit() const;
  /** Min limit of distance soldier can travel at one step. */
  [[nodiscard]] int MinSoldierTravelDistanceLimit() const;
  /** Base limit of travel distance of soldier. */
  [[nodiscard]] int BaseSoldierTravelDistanceLimit() const;
  /** Max limit of distance drone can travel at one step. */
  [[nodiscard]] int MaxDroneTravelDistanceLimit() const;
  /** Min limit of distance drone can travel at one step. */
  [[nodiscard]] int MinDroneTravelDistanceLimit() const;
  /** Base limit of travel distance of drone. */
  [[nodiscard]] int BaseDroneTravelDistanceLimit() const;
  /** Unit movement speed (tiles per second). */
  [[nodiscard]] double UnitMoveSpeed() const;

 private:
  /** Array with weapon max ammo. */
  std::array<std::optional<int>, kWeaponInfo.size()> weapon_max_ammo_;
  /** Array with weapon mass. */
  std::array<int, kWeaponInfo.size()> weapon_mass_;
  /** Array with weapon base damage. */
  std::array<int, kWeaponInfo.size()> weapon_base_damage_;
  /** Array with armor defence. */
  std::array<int, kArmorInfo.size()> armor_defence_;
  /** Array with armor mass. */
  std::array<int, kArmorInfo.size()> armor_mass_;
  /** Effect of advanced tech level. Base value is multiplied or divided by the effect to get final value. */
  double advanced_tech_level_effect_;
  /** Default number of soldiers/drones in squad. */
  int squad_size_;

  /** Number of parts world map divided into by each dimension during generation. */
  int world_map_subdivision_;
  /** Size of world map part. */
  int world_map_part_size_;
  /** Max number of houses on map. */
  int world_map_max_house_count_;

  /** Min size of enemy squad. */
  int min_enemy_squad_size_;
  /** Min difficulty when enemies begin to use laser weapons. */
  double laser_weapon_difficulty_threshold_;
  /** Min difficulty when enemies begin to wear composite armor. */
  double composite_armor_difficulty_threshold_;
  /** Probability of enemy soldier having secondary weapon - pistol. */
  double enemy_secondary_weapon_probability_;

  /** Base health of soldier. */
  int soldier_base_health_;
  /** Base health of drone. */
  int drone_base_health_;

  /** Max limit of distance soldier can travel at one step. */
  int max_soldier_travel_distance_limit_;
  /** Min limit of distance soldier can travel at one step. */
  int min_soldier_travel_distance_limit_;
  /** Base limit of travel distance of soldier. */
  int base_soldier_travel_distance_limit_;
  /** Max limit of distance drone can travel at one step. */
  int max_drone_travel_distance_limit_;
  /** Min limit of distance drone can travel at one step. */
  int min_drone_travel_distance_limit_;
  /** Base limit of travel distance of drone. */
  int base_drone_travel_distance_limit_;
  /** Unit movement speed (tiles per second). */
  double unit_move_speed_;

};

}
