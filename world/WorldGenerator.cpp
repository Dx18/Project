#include "WorldGenerator.h"

namespace world {

WorldGenerator::WorldGenerator(const config::GameConfig &game_config, std::mt19937 random)
    : game_config_(game_config), random_(random) {

}

World WorldGenerator::GenerateWorld(std::vector<std::unique_ptr<unit::Unit>> &&player_units, double difficulty) {
  map::WorldMap map = GenerateMap();
  std::vector<std::unique_ptr<unit::Unit>> enemy_units = GenerateEnemyUnits(difficulty);

  for (size_t i = 0; i < player_units.size(); ++i) {
    player_units[i]->SetPosition(util::Vector3<double>{0.5, static_cast<double>(i) + 0.5, 0.0});
  }

  util::Vector2<size_t> map_size = map.Size();
  for (size_t i = 0; i < enemy_units.size(); ++i) {
    enemy_units[i]->SetPosition(util::Vector3<double>{
        static_cast<double>(map_size.x) - 0.5,
        static_cast<double>(map_size.y) - 0.5 - static_cast<double>(i),
        0.0
    });
  }

  return World(map, std::move(player_units), std::move(enemy_units));
}

map::WorldMap WorldGenerator::GenerateMap() {
  enum WorldPart {
    kRoad,
    kLawn,
    kHouse
  };

  enum BranchRoadDirection {
    kNone,
    kUp,
    kDown
  };

  size_t subdivision = game_config_.WorldMapSubdivision();
  std::vector<WorldPart> parts(subdivision * subdivision, WorldPart::kLawn);

  size_t main_road_line = std::uniform_int_distribution<size_t>(1, subdivision - 2)(random_);

  std::vector<BranchRoadDirection> branches(subdivision, BranchRoadDirection::kNone);

  branches[0] = BranchRoadDirection::kUp;
  for (size_t column = 1; column < subdivision; ++column) {
    int choice = 1;
    if (branches[column - 1] == BranchRoadDirection::kNone) {
      choice = std::uniform_int_distribution<int>(0, 2)(random_);
    } else if (branches[column - 1] == BranchRoadDirection::kUp) {
      choice = std::uniform_int_distribution<int>(0, 1)(random_);
    } else if (branches[column - 1] == BranchRoadDirection::kDown) {
      choice = std::uniform_int_distribution<int>(1, 2)(random_);
    }

    if (choice == 0) {
      branches[column] = BranchRoadDirection::kDown;
    } else if (choice == 1) {
      branches[column] = BranchRoadDirection::kNone;
    } else {
      branches[column] = BranchRoadDirection::kUp;
    }
  }

  for (size_t column = 0; column < subdivision; ++column) {
    parts[main_road_line * subdivision + column] = WorldPart::kRoad;

    if (branches[column] == BranchRoadDirection::kUp) {
      for (size_t row = 0; row < main_road_line; ++row) {
        parts[row * subdivision + column] = WorldPart::kRoad;
      }
    } else if (branches[column] == BranchRoadDirection::kDown) {
      for (size_t row = main_road_line + 1; row < subdivision; ++row) {
        parts[row * subdivision + column] = WorldPart::kRoad;
      }
    }
  }

  std::vector<util::Vector2<size_t>> lawn_positions;
  for (size_t row = 0; row < subdivision; ++row) {
    for (size_t column = 0; column < subdivision; ++column) {
      if (parts[row * subdivision + column] == WorldPart::kLawn) {
        lawn_positions.push_back({column, row});
      }
    }
  }

  std::shuffle(lawn_positions.begin(), lawn_positions.end(), random_);

  size_t max_house_count = game_config_.WorldMapMaxHouseCount();
  for (size_t i = 0; i < std::min(lawn_positions.size(), max_house_count); ++i) {
    parts[lawn_positions[i].y * subdivision + lawn_positions[i].x] = WorldPart::kHouse;
  }

  size_t part_size = game_config_.WorldMapPartSize();
  map::WorldMap result({subdivision * part_size, subdivision * part_size});

  static const map::Wall kNoWall = map::Wall(map::WallForm::kNoWall);
  static const map::Wall kHalfWall = map::Wall(map::WallForm::kHalf);
  static const map::Wall kFullWall = map::Wall(map::WallForm::kFull);

  for (size_t part_row = 0; part_row < subdivision; ++part_row) {
    for (size_t part_column = 0; part_column < subdivision; ++part_column) {
      WorldPart part = parts[part_row * subdivision + part_column];

      map::FloorMaterialType base_floor = map::FloorMaterialType::kGrass;
      if (part == WorldPart::kRoad) {
        base_floor = map::FloorMaterialType::kAsphalt;
      }

      std::vector<map::Tile> tiles(part_size * part_size, map::Tile(
          {kNoWall, kNoWall, kNoWall, kNoWall}, base_floor
      ));

      if (part == WorldPart::kHouse) {
        for (size_t row = 1; row < part_size - 1; ++row) {
          for (size_t column = 1; column < part_size - 1; ++column) {
            tiles[row * part_size + column].floor = map::FloorMaterialType::kWood;
          }
        }

        for (size_t row = 1; row < part_size - 1; ++row) {
          tiles[row * part_size + 1].walls[map::Tile::kWallLeft] = kFullWall;
          tiles[row * part_size + part_size - 2].walls[map::Tile::kWallRight] = kFullWall;
        }
        for (size_t column = 1; column < part_size - 1; ++column) {
          tiles[1 * part_size + column].walls[map::Tile::kWallUp] = kFullWall;
          tiles[(part_size - 2) * part_size + column].walls[map::Tile::kWallDown] = kFullWall;
        }

        size_t entrance_side = std::uniform_int_distribution<size_t>(0, map::Tile::kWallCount - 1)(random_);
        if (entrance_side == map::Tile::kWallUp) {
          tiles[1 * part_size + part_size / 2].walls[map::Tile::kWallUp] = kNoWall;
        } else if (entrance_side == map::Tile::kWallRight) {
          tiles[(part_size / 2) * part_size + part_size - 2].walls[map::Tile::kWallRight] = kNoWall;
        } else if (entrance_side == map::Tile::kWallDown) {
          tiles[(part_size - 2) * part_size + part_size / 2].walls[map::Tile::kWallDown] = kNoWall;
        } else if (entrance_side == map::Tile::kWallLeft) {
          tiles[(part_size / 2) * part_size + 1].walls[map::Tile::kWallLeft] = kNoWall;
        }
      }

      for (size_t row = 0; row < part_size; ++row) {
        for (size_t column = 0; column < part_size; ++column) {
          result.Set(
              {column + part_column * part_size, row + part_row * part_size},
              tiles[row * part_size + column]
          );
        }
      }
    }
  }

  return result;
}

std::vector<std::unique_ptr<unit::Unit>> WorldGenerator::GenerateEnemyUnits(double difficulty) {
  headquarters_model::Resources enemy_resources;
  enemy_resources.matter = 0;

  headquarters_model::tech::Tech enemy_tech(game_config_, enemy_resources);

  size_t enemy_count = static_cast<size_t>(std::sqrt(difficulty)) + game_config_.MinEnemySquadSize();

  size_t soldier_count = std::uniform_int_distribution<size_t>(0, enemy_count)(random_);
  size_t drone_count = enemy_count - soldier_count;

  std::unique_ptr<unit::soldier::weapon::ISoldierWeaponFactory> soldier_weapon_factory;
  std::unique_ptr<unit::drone::weapon::IDroneWeaponFactory> drone_weapon_factory;
  if (difficulty < game_config_.LaserWeaponDifficultyThreshold()) {
    enemy_tech.ResearchWeapon(object_database::WeaponTechType::kFirearm);
    soldier_weapon_factory = std::make_unique<unit::soldier::weapon::firearm::SoldierFirearmWeaponFactory>(enemy_tech);
    drone_weapon_factory = std::make_unique<unit::drone::weapon::firearm::DroneFirearmWeaponFactory>(enemy_tech);
  } else {
    enemy_tech.ResearchWeapon(object_database::WeaponTechType::kLaser);
    soldier_weapon_factory = std::make_unique<unit::soldier::weapon::laser::SoldierLaserWeaponFactory>(enemy_tech);
    drone_weapon_factory = std::make_unique<unit::drone::weapon::laser::DroneLaserWeaponFactory>(enemy_tech);
  }

  std::unique_ptr<unit::soldier::armor::ISoldierArmorFactory> soldier_armor_factory;
  std::unique_ptr<unit::drone::armor::IDroneArmorFactory> drone_armor_factory;
  if (difficulty < game_config_.CompositeArmorDifficultyThreshold()) {
    enemy_tech.ResearchArmor(object_database::ArmorTechType::kStandard);
    soldier_armor_factory = std::make_unique<unit::soldier::armor::standard::SoldierStandardArmorFactory>(enemy_tech);
    drone_armor_factory = std::make_unique<unit::drone::armor::standard::DroneStandardArmorFactory>(enemy_tech);
  } else {
    enemy_tech.ResearchArmor(object_database::ArmorTechType::kComposite);
    soldier_armor_factory = std::make_unique<unit::soldier::armor::composite::SoldierCompositeArmorFactory>(enemy_tech);
    drone_armor_factory = std::make_unique<unit::drone::armor::composite::DroneCompositeArmorFactory>(enemy_tech);
  }

  std::vector<std::unique_ptr<unit::Unit>> units;

  for (size_t index = 0; index < soldier_count; ++index) {
    unit::soldier::SoldierBuilder soldier;

    std::stringstream name;
    name << "Enemy soldier " << index + 1;
    soldier.WithName(name.str());

    soldier.WithBaseHealth(game_config_.SoldierBaseHealth());

    static const size_t kSoldierWeaponClassCount = 4;

    size_t primary_weapon_class
        = std::uniform_int_distribution<size_t>(0, kSoldierWeaponClassCount - 1)(random_);
    if (primary_weapon_class == 0) {
      soldier.WithPrimaryWeapon(soldier_weapon_factory->CreatePistol());
    } else if (primary_weapon_class == 1) {
      soldier.WithPrimaryWeapon(soldier_weapon_factory->CreateShotgun());
    } else if (primary_weapon_class == 2) {
      soldier.WithPrimaryWeapon(soldier_weapon_factory->CreateSniperRifle());
    } else if (primary_weapon_class == 3) {
      soldier.WithPrimaryWeapon(soldier_weapon_factory->CreateMachineGun());
    }

    if (std::uniform_real_distribution<double>(0.0, 1.0)(random_)
        < game_config_.EnemySecondaryWeaponProbability()) {
      size_t secondary_weapon_class
          = std::uniform_int_distribution<size_t>(0, kSoldierWeaponClassCount - 1)(random_);
      if (secondary_weapon_class == 0) {
        soldier.WithSecondaryWeapon(soldier_weapon_factory->CreatePistol());
      } else if (secondary_weapon_class == 1) {
        soldier.WithSecondaryWeapon(soldier_weapon_factory->CreateShotgun());
      } else if (secondary_weapon_class == 2) {
        soldier.WithSecondaryWeapon(soldier_weapon_factory->CreateSniperRifle());
      } else if (secondary_weapon_class == 3) {
        soldier.WithSecondaryWeapon(soldier_weapon_factory->CreateMachineGun());
      }
    }

    soldier.WithArmor(soldier_armor_factory->CreateArmor());

    unit::soldier::Soldier soldier_result = soldier.Build();
    soldier_result.SetHealth(soldier_result.MaxHealth());
    units.push_back(std::make_unique<unit::soldier::Soldier>(std::move(soldier_result)));
  }

  for (size_t index = 0; index < drone_count; ++index) {
    unit::drone::DroneBuilder drone;

    std::stringstream name;
    name << "Enemy drone " << index + 1;
    drone.WithName(name.str());

    drone.WithBaseHealth(game_config_.DroneBaseHealth());

    static const size_t kDroneWeaponClassCount = 1;

    size_t weapon_class = std::uniform_int_distribution<size_t>(0, kDroneWeaponClassCount - 1)(random_);
    if (weapon_class == 0) {
      drone.WithWeapon(drone_weapon_factory->CreateMachineGun());
    }

    drone.WithArmor(drone_armor_factory->CreateArmor());

    unit::drone::Drone drone_result = drone.Build();
    drone_result.SetHealth(drone_result.MaxHealth());
    units.push_back(std::make_unique<unit::drone::Drone>(std::move(drone_result)));
  }

  return units;
}

}
