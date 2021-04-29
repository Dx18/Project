#include "GameConfig.h"

namespace config {

GameConfig::GameConfig(const ConfigSectionStructure &section)
    : weapon_max_ammo_(), weapon_mass_(), armor_defence_(), armor_mass_(), advanced_tech_level_effect_() {
  for (const WeaponInfo &weapon_info : kWeaponInfo) {
    if (weapon_info.has_max_ammo) {
      weapon_max_ammo_[weapon_info.type] = std::stoi(section.values.at(weapon_info.name + "_max_ammo"));
    }
    weapon_mass_[weapon_info.type] = std::stoi(section.values.at(weapon_info.name + "_mass"));
  }
  for (const ArmorInfo &armor_info : kArmorInfo) {
    armor_defence_[armor_info.type] = std::stoi(section.values.at(armor_info.name + "_defence"));
    armor_mass_[armor_info.type] = std::stoi(section.values.at(armor_info.name + "_mass"));
  }

  advanced_tech_level_effect_ = std::stod(section.values.at("advanced_tech_level_effect"));
  squad_size_ = std::stoi(section.values.at("squad_size"));

  world_map_subdivision_ = std::stoi(section.values.at("world_map_subdivision"));
  world_map_part_size_ = std::stoi(section.values.at("world_map_part_size"));
  world_map_max_house_count_ = std::stoi(section.values.at("world_map_max_house_count"));

  min_enemy_squad_size_ = std::stoi(section.values.at("min_enemy_squad_size"));
  laser_weapon_difficulty_threshold_ = std::stod(section.values.at("laser_weapon_difficulty_threshold"));
  composite_armor_difficulty_threshold_ = std::stod(section.values.at("composite_armor_difficulty_threshold"));
  enemy_secondary_weapon_probability_ = std::stod(section.values.at("enemy_secondary_weapon_probability"));
}

std::optional<int> GameConfig::WeaponMaxAmmo(WeaponType type) const {
  return weapon_max_ammo_[type];
}

int GameConfig::WeaponMass(WeaponType type) const {
  return weapon_mass_[type];
}

int GameConfig::ArmorDefence(ArmorType type) const {
  return armor_defence_[type];
}

int GameConfig::ArmorMass(ArmorType type) const {
  return armor_mass_[type];
}

double GameConfig::AdvancedTechLevelEffect() const {
  return advanced_tech_level_effect_;
}

int GameConfig::SquadSize() const {
  return squad_size_;
}

int GameConfig::WorldMapSubdivision() const {
  return world_map_subdivision_;
}

int GameConfig::WorldMapPartSize() const {
  return world_map_part_size_;
}

int GameConfig::WorldMapMaxHouseCount() const {
  return world_map_max_house_count_;
}

int GameConfig::MinEnemySquadSize() const {
  return min_enemy_squad_size_;
}

double GameConfig::LaserWeaponDifficultyThreshold() const {
  return laser_weapon_difficulty_threshold_;
}

double GameConfig::CompositeArmorDifficultyThreshold() const {
  return composite_armor_difficulty_threshold_;
}

double GameConfig::EnemySecondaryWeaponProbability() const {
  return enemy_secondary_weapon_probability_;
}

}
