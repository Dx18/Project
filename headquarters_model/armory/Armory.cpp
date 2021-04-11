#include "Armory.h"

namespace headquarters_model::armory {

Armory::Armory(Resources &resources)
    : weapon_count_(), armor_count_(), resources_(resources) {
  std::fill(weapon_count_.begin(), weapon_count_.end(), 0);
  std::fill(armor_count_.begin(), armor_count_.end(), 0);
}

Armory::Armory(const config::ConfigSectionStructure &armory_info, Resources &resources)
    : weapon_count_(), armor_count_(), resources_(resources) {
  for (const WeaponInfo &weapon_info : kWeaponInfo) {
    weapon_count_[weapon_info.type] = std::stoi(armory_info.values.at(weapon_info.name + "_count"));
  }
  for (const ArmorInfo &armor_info : kArmorInfo) {
    armor_count_[armor_info.tech_type] =
        std::stoi(armory_info.values.at(armor_info.name + "_tech_level"));
  }
}

size_t Armory::WeaponCount(WeaponType type) const {
  return weapon_count_[type];
}

BuildResult Armory::BuildWeapon(WeaponType type) {
  ++weapon_count_[type];
  return BuildResult::kBuilt;
}

size_t Armory::ArmorCount(ArmorType type) const {
  return armor_count_[type];
}

BuildResult Armory::BuildArmor(ArmorType type) {
  ++armor_count_[type];
  return BuildResult::kBuilt;
}

}
