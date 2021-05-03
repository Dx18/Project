#include "Tech.h"

namespace headquarters_model::tech {

Tech::Tech(const config::GameConfig &game_config, Resources &resources)
    : game_config_(game_config), weapon_tech_level_(), armor_tech_level_(), resources_(resources) {
  std::fill(weapon_tech_level_.begin(), weapon_tech_level_.end(), TechLevel::kNotResearched);
  std::fill(armor_tech_level_.begin(), armor_tech_level_.end(), TechLevel::kNotResearched);
}

Tech::Tech(const config::GameConfig &game_config, const config::ConfigSectionStructure &tech_info, Resources &resources)
    : game_config_(game_config), weapon_tech_level_(), armor_tech_level_(), resources_(resources) {
  for (const WeaponTechInfo &weapon_tech_info : kWeaponTechInfo) {
    weapon_tech_level_[weapon_tech_info.tech_type] =
        tech_level_from_int(std::stoi(tech_info.values.at(weapon_tech_info.name + "_tech_level")));
  }
  for (const ArmorTechInfo &armor_tech_info : kArmorTechInfo) {
    armor_tech_level_[armor_tech_info.tech_type] =
        tech_level_from_int(std::stoi(tech_info.values.at(armor_tech_info.name + "_tech_level")));
  }
}

std::optional<int> Tech::WeaponMaxAmmo(WeaponType type) const {
  std::optional<int> base_value = game_config_.WeaponMaxAmmo(type);
  if (!base_value.has_value()) {
    return {};
  }

  WeaponTechType tech_type = kWeaponInfo[type].tech_type;
  return CalculateIncreasing(weapon_tech_level_[tech_type], base_value.value());
}

int Tech::WeaponMass(WeaponType type) const {
  int base_value = game_config_.WeaponMass(type);

  WeaponTechType tech_type = kWeaponInfo[type].tech_type;
  return CalculateDecreasing(weapon_tech_level_[tech_type], base_value);
}

int Tech::ArmorDefence(ArmorType type) const {
  int base_value = game_config_.ArmorDefence(type);

  ArmorTechType tech_type = kArmorInfo[type].tech_type;
  return CalculateIncreasing(armor_tech_level_[tech_type], base_value);
}

int Tech::ArmorMass(ArmorType type) const {
  int base_value = game_config_.ArmorMass(type);

  ArmorTechType tech_type = kArmorInfo[type].tech_type;
  return CalculateDecreasing(armor_tech_level_[tech_type], base_value);
}

TechLevel Tech::WeaponTechLevel(WeaponTechType tech_type) const {
  return weapon_tech_level_[tech_type];
}

TechLevel Tech::ArmorTechLevel(ArmorTechType tech_type) const {
  return armor_tech_level_[tech_type];
}

ResearchResult Tech::ResearchWeapon(WeaponTechType tech_type) {
  TechLevel &level = weapon_tech_level_[tech_type];
  if (level == TechLevel::kAdvanced) {
    return ResearchResult::kAlreadyMaxLevel;
  }
  level = next_tech_level(level);
  return ResearchResult::kResearched;
}

ResearchResult Tech::ResearchArmor(ArmorTechType tech_type) {
  TechLevel &level = armor_tech_level_[tech_type];
  if (level == TechLevel::kAdvanced) {
    return ResearchResult::kAlreadyMaxLevel;
  }
  level = next_tech_level(level);
  return ResearchResult::kResearched;
}

double Tech::TechLevelEffect(TechLevel tech_level) const {
  if (tech_level == TechLevel::kBasic) {
    return 1.0;
  } else if (tech_level == TechLevel::kAdvanced) {
    return game_config_.AdvancedTechLevelEffect();
  }
  return 0.0;
}

int Tech::CalculateIncreasing(TechLevel tech_level, int base_value) const {
  double effect = TechLevelEffect(tech_level);
  return static_cast<int>(std::ceil(base_value * effect));
}

int Tech::CalculateDecreasing(TechLevel tech_level, int base_value) const {
  double effect = TechLevelEffect(tech_level);
  if (effect == 0.0) {
    return 0;
  }
  return static_cast<int>(std::ceil(base_value / effect));
}

}
