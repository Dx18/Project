#include "Tech.h"

namespace headquarters_model::tech {

Tech::Tech(const config::GameConfig &game_config, const config::ConfigSectionStructure &tech_info)
    : game_config_(game_config),
      firearm_weapon_tech_level_(tech_level_from_int(
          std::stoi(tech_info.values.at("firearm_weapon_tech_level")))),
      laser_weapon_tech_level_(tech_level_from_int(
          std::stoi(tech_info.values.at("laser_weapon_tech_level")))),
      standard_armor_tech_level_(tech_level_from_int(
          std::stoi(tech_info.values.at("standard_armor_tech_level")))),
      composite_armor_tech_level_(tech_level_from_int(
          std::stoi(tech_info.values.at("composite_armor_tech_level")))) {

}

const config::GameConfig &Tech::GameConfig() const {
  return game_config_;
}

TechLevel Tech::FirearmWeaponTechLevel() const {
  return firearm_weapon_tech_level_;
}

void Tech::SetFirearmWeaponTechLevel(TechLevel new_tech_level) {
  firearm_weapon_tech_level_ = new_tech_level;
}

TechLevel Tech::LaserWeaponTechLevel() const {
  return laser_weapon_tech_level_;
}

void Tech::SetLaserWeaponTechLevel(TechLevel new_tech_level) {
  laser_weapon_tech_level_ = new_tech_level;
}

TechLevel Tech::StandardArmorTechLevel() const {
  return standard_armor_tech_level_;
}

void Tech::SetStandardArmorTechLevel(TechLevel new_tech_level) {
  standard_armor_tech_level_ = new_tech_level;
}

TechLevel Tech::CompositeArmorTechLevel() const {
  return composite_armor_tech_level_;
}

void Tech::SetCompositeArmorTechLevel(TechLevel new_tech_level) {
  composite_armor_tech_level_ = new_tech_level;
}

int Tech::CalculateFirearmWeaponMaxAmmo(int base_max_ammo) const {
  return CalculateIncreasing(firearm_weapon_tech_level_, base_max_ammo);
}

int Tech::CalculateFirearmWeaponMass(int base_mass) const {
  return CalculateDecreasing(firearm_weapon_tech_level_, base_mass);
}

int Tech::CalculateLaserWeaponMass(int base_mass) const {
  return CalculateDecreasing(laser_weapon_tech_level_, base_mass);
}

int Tech::CalculateStandardArmorDefence(int base_defence) const {
  return CalculateIncreasing(standard_armor_tech_level_, base_defence);
}

int Tech::CalculateStandardArmorMass(int base_mass) const {
  return CalculateDecreasing(standard_armor_tech_level_, base_mass);
}

int Tech::CalculateCompositeArmorDefence(int base_defence) const {
  return CalculateIncreasing(composite_armor_tech_level_, base_defence);
}

int Tech::CalculateCompositeArmorMass(int base_mass) const {
  return CalculateDecreasing(composite_armor_tech_level_, base_mass);
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
