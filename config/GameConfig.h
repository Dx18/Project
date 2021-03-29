#pragma once

#include "ConfigSectionStructure.h"

namespace config {

/** Game process config. */
struct GameConfig {
  /** Default max ammo for soldier firearm pistol. */
  int soldier_firearm_pistol_max_ammo;
  /** Default mass for soldier firearm pistol. */
  int soldier_firearm_pistol_mass;
  /** Default max ammo for soldier firearm shotgun. */
  int soldier_firearm_shotgun_max_ammo;
  /** Default mass for soldier firearm shotgun. */
  int soldier_firearm_shotgun_mass;
  /** Default max ammo for soldier firearm sniper rifle. */
  int soldier_firearm_sniper_rifle_max_ammo;
  /** Default mass for soldier firearm sniper rifle. */
  int soldier_firearm_sniper_rifle_mass;
  /** Default max ammo for soldier firearm machine gun. */
  int soldier_firearm_machine_gun_max_ammo;
  /** Default mass for soldier firearm machine gun. */
  int soldier_firearm_machine_gun_mass;
  /** Default mass for soldier laser pistol. */
  int soldier_laser_pistol_mass;
  /** Default mass for soldier laser shotgun. */
  int soldier_laser_shotgun_mass;
  /** Default mass for soldier laser sniper rifle. */
  int soldier_laser_sniper_rifle_mass;
  /** Default mass for soldier laser machine gun. */
  int soldier_laser_machine_gun_mass;
  /** Default max ammo for drone firearm machine gun. */
  int drone_firearm_machine_gun_max_ammo;
  /** Default mass for drone firearm machine gun. */
  int drone_firearm_machine_gun_mass;
  /** Default mass for drone laser machine gun. */
  int drone_laser_machine_gun_mass;

  explicit GameConfig(const ConfigSectionStructure &section);

};

}
