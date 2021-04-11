#include "Armory.h"

namespace headquarters_model::armory {

Armory::Armory(const config::ConfigSectionStructure &armory_info)
    : weapon_count_(), armor_count_() {
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

BuildResult Armory::BuildWeapon(WeaponType type, Resources &resources) {
  ++weapon_count_[type];
  return BuildResult::kBuilt;
}

size_t Armory::ArmorCount(ArmorType type) const {
  return armor_count_[type];
}

BuildResult Armory::BuildArmor(ArmorType type, Resources &resources) {
  ++armor_count_[type];
  return BuildResult::kBuilt;
}

}
