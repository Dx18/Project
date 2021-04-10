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

int Tech::FirearmWeaponMaxAmmo(int base_max_ammo) const {
  double effect = TechLevelEffect(composite_armor_tech_level_);
  if (effect == 0.0) {
    return 0;
  }
  return static_cast<int>(std::ceil(base_max_ammo * effect));
}

int Tech::FirearmWeaponMass(int base_mass) const {
  double effect = TechLevelEffect(composite_armor_tech_level_);
  if (effect == 0.0) {
    return 0;
  }
  return std::max(1, static_cast<int>(std::floor(base_mass / effect)));
}

int Tech::LaserWeaponMass(int base_mass) const {
  double effect = TechLevelEffect(composite_armor_tech_level_);
  if (effect == 0.0) {
    return 0;
  }
  return std::max(1, static_cast<int>(std::floor(base_mass / effect)));
}

int Tech::StandardArmorDefence(int base_defence) const {
  double effect = TechLevelEffect(composite_armor_tech_level_);
  if (effect == 0.0) {
    return 0;
  }
  return static_cast<int>(std::ceil(base_defence * effect));
}

int Tech::StandardArmorMass(int base_mass) const {
  double effect = TechLevelEffect(composite_armor_tech_level_);
  if (effect == 0.0) {
    return 0;
  }
  return std::max(1, static_cast<int>(std::floor(base_mass / effect)));
}

int Tech::CompositeArmorDefence(int base_defence) const {
  double effect = TechLevelEffect(composite_armor_tech_level_);
  if (effect == 0.0) {
    return 0;
  }
  return static_cast<int>(std::ceil(base_defence * effect));
}

int Tech::CompositeArmorMass(int base_mass) const {
  double effect = TechLevelEffect(composite_armor_tech_level_);
  if (effect == 0.0) {
    return 0;
  }
  return std::max(1, static_cast<int>(std::floor(base_mass / effect)));
}

double Tech::TechLevelEffect(TechLevel tech_level) const {
  if (firearm_weapon_tech_level_ == TechLevel::kBasic) {
    return 1.0;
  } else if (firearm_weapon_tech_level_ == TechLevel::kAdvanced) {
    return game_config_.advanced_tech_level_effect;
  }
  return 0.0;
}

}
