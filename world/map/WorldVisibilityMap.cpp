#include "WorldVisibilityMap.h"

namespace world::map {

WorldVisibilityMap::PositionInfo::PositionInfo()
    : position({0, 0}), visibility(0.0), distance(0.0) {

}

WorldVisibilityMap::PositionInfo::PositionInfo(util::Vector2<size_t> _position, double _visibility, double _distance)
    : position(_position), visibility(_visibility), distance(_distance) {

}

WorldVisibilityMap::WorldVisibilityMap(const config::GameConfig &game_config, const WorldMap &map,
                                       const util::Vector2<size_t> &position)
    : map_size_(map.Size()), position_(position), positions_(map_size_.x * map_size_.y) {
  map.CheckIfContainsPoint(position);

  for (size_t row = 0; row < map_size_.y; ++row) {
    for (size_t column = 0; column < map_size_.x; ++column) {
      positions_[row * map_size_.x + column] = CalculatePositionInfo({column, row});
    }
  }
}

std::optional<WorldVisibilityMap::PositionInfo> WorldVisibilityMap::GetPositionInfo(const util::Vector2<size_t> &position) {
  if (position.y >= map_size_.y || position.x >= map_size_.x) {
    return {};
  }
  return positions_[position.y * map_size_.x + position.x];
}

WorldVisibilityMap::PositionInfo
WorldVisibilityMap::CalculatePositionInfo(const config::GameConfig &game_config, const world::map::WorldMap &map,
                                          util::Vector2<size_t> position) {
  util::Vector2<double> direction = {
      static_cast<double>(position.x) - static_cast<double>(position_.x),
      static_cast<double>(position.y) - static_cast<double>(position_.y)
  };

  util::Vector2<double> current_position = {position_.x + 0.5, position_.y + 0.5};
  util::Vector2<ssize_t> current_tile_position = {static_cast<ssize_t>(position.x), static_cast<ssize_t>(position.y)};

  double visibility = 1.0;

  while (visibility > 0.0
      && current_tile_position.y >= 0 && current_tile_position.y < map_size_.y
      && current_tile_position.x >= 0 && current_tile_position.x < map_size_.x
      && (current_tile_position.x != position.x || current_tile_position.y != position.y)) {
    double t_vertical = std::numeric_limits<double>::infinity();
    if (direction.y > 0) {
      t_vertical = (static_cast<double>(current_tile_position.y + 1) - current_position.y) / direction.y;
    } else if (direction.y < 0) {
      t_vertical = (current_position.y - static_cast<double>(current_tile_position.y)) / -direction.y;
    }

    double t_horizontal = std::numeric_limits<double>::infinity();
    if (direction.x > 0) {
      t_horizontal = (static_cast<double>(current_tile_position.x + 1) - current_position.x) / direction.x;
    } else if (direction.x < 0) {
      t_horizontal = (current_position.x - static_cast<double>(current_tile_position.x)) / -direction.x;
    }

    double min_t = std::min(t_vertical, t_horizontal);
    WallForm obstacle = WallForm::kFull;
    if (t_vertical == min_t) {
      WallForm current_wall = WallForm::kNoWall;

      std::optional<Tile> current_tile
          = map.Get({
                        static_cast<size_t>(current_tile_position.x),
                        static_cast<size_t>(current_tile_position.y)
                    });

      if (direction.y > 0) {
        if (current_tile.has_value()) {
          current_wall = current_tile->walls[Tile::kWallDown].form;
        }

        if (current_tile_position.y < map_size_.y - 1) {
          std::optional<Tile> next_tile
              = map.Get({
                            static_cast<size_t>(current_tile_position.x),
                            static_cast<size_t>(current_tile_position.y + 1)
                        });

          if (next_tile.has_value()) {
            current_wall = std::max(current_wall, next_tile->walls[Tile::kWallUp].form);
          }
        }
      } else if (direction.y < 0) {
        if (current_tile.has_value()) {
          current_wall = current_tile->walls[Tile::kWallUp].form;
        }

        if (current_tile_position.y > 0) {
          std::optional<Tile> next_tile
              = map.Get({
                            static_cast<size_t>(current_tile_position.x),
                            static_cast<size_t>(current_tile_position.y - 1)
                        });

          if (next_tile.has_value()) {
            current_wall = std::max(current_wall, next_tile->walls[Tile::kWallDown].form);
          }
        }
      }

      obstacle = std::min(obstacle, current_wall);
    }
    if (t_horizontal == min_t) {
      WallForm current_wall = WallForm::kNoWall;

      std::optional<Tile> current_tile
          = map.Get({
                        static_cast<size_t>(current_tile_position.x),
                        static_cast<size_t>(current_tile_position.y)
                    });

      if (direction.x > 0) {
        if (current_tile.has_value()) {
          current_wall = current_tile->walls[Tile::kWallRight].form;
        }

        if (current_tile_position.x < map_size_.x - 1) {
          std::optional<Tile> next_tile
              = map.Get({
                            static_cast<size_t>(current_tile_position.x + 1),
                            static_cast<size_t>(current_tile_position.y)
                        });

          if (next_tile.has_value()) {
            current_wall = std::max(current_wall, next_tile->walls[Tile::kWallLeft].form);
          }
        }
      } else if (direction.x < 0) {
        if (current_tile.has_value()) {
          current_wall = current_tile->walls[Tile::kWallLeft].form;
        }

        if (current_tile_position.x > 0) {
          std::optional<Tile> next_tile
              = map.Get({
                            static_cast<size_t>(current_tile_position.x - 1),
                            static_cast<size_t>(current_tile_position.y)
                        });

          if (next_tile.has_value()) {
            current_wall = std::max(current_wall, next_tile->walls[Tile::kWallRight].form);
          }
        }
      }

      obstacle = std::min(obstacle, current_wall);
    }

    if (obstacle == WallForm::kHalf) {
      visibility *= game_config.HalfWallVisibilityEffect();
    } else if (obstacle == WallForm::kFull) {
      visibility = 0.0;
    }
  }

  double distance = std::sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
  return PositionInfo(position, visibility, distance);
}

}
