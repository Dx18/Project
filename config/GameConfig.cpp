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

}
