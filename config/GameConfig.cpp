#include "GameConfig.h"

namespace config {

GameConfig::GameConfig(const ConfigSectionStructure &section)
    : soldier_firearm_pistol_max_ammo(std::stoi(section.values.at("soldier_firearm_pistol_max_ammo"))),
      soldier_firearm_pistol_mass(std::stoi(section.values.at("soldier_firearm_pistol_mass"))),
      soldier_firearm_shotgun_max_ammo(std::stoi(section.values.at("soldier_firearm_shotgun_max_ammo"))),
      soldier_firearm_shotgun_mass(std::stoi(section.values.at("soldier_firearm_shotgun_mass"))),
      soldier_firearm_sniper_rifle_max_ammo(std::stoi(section.values.at("soldier_firearm_sniper_rifle_max_ammo"))),
      soldier_firearm_sniper_rifle_mass(std::stoi(section.values.at("soldier_firearm_sniper_rifle_mass"))),
      soldier_firearm_machine_gun_max_ammo(std::stoi(section.values.at("soldier_firearm_machine_gun_max_ammo"))),
      soldier_firearm_machine_gun_mass(std::stoi(section.values.at("soldier_firearm_machine_gun_mass"))),
      soldier_laser_pistol_mass(std::stoi(section.values.at("soldier_laser_pistol_mass"))),
      soldier_laser_shotgun_mass(std::stoi(section.values.at("soldier_laser_shotgun_mass"))),
      soldier_laser_sniper_rifle_mass(std::stoi(section.values.at("soldier_laser_sniper_rifle_mass"))),
      soldier_laser_machine_gun_mass(std::stoi(section.values.at("soldier_laser_machine_gun_mass"))),
      soldier_standard_armor_defence(std::stoi(section.values.at("soldier_standard_armor_defence"))),
      soldier_standard_armor_mass(std::stoi(section.values.at("soldier_standard_armor_mass"))),
      soldier_composite_armor_defence(std::stoi(section.values.at("soldier_composite_armor_defence"))),
      soldier_composite_armor_mass(std::stoi(section.values.at("soldier_composite_armor_mass"))),
      drone_firearm_machine_gun_max_ammo(std::stoi(section.values.at("drone_firearm_machine_gun_max_ammo"))),
      drone_firearm_machine_gun_mass(std::stoi(section.values.at("drone_firearm_machine_gun_mass"))),
      drone_laser_machine_gun_mass(std::stoi(section.values.at("drone_laser_machine_gun_mass"))),
      drone_standard_armor_defence(std::stoi(section.values.at("drone_standard_armor_defence"))),
      drone_standard_armor_mass(std::stoi(section.values.at("drone_standard_armor_mass"))) {

}

}
