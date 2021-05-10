#include "Tile.h"

namespace world::map {

Tile::Tile(std::array<Wall, kWallCount> _walls, FloorMaterialType _floor)
:  walls(_walls), floor(_floor) {

}

bool Tile::operator==(const Tile &other) const {
  return walls == other.walls && floor == other.floor;
}

bool Tile::operator!=(const Tile &other) const {
  return !(*this == other);
}

}

namespace std {

size_t hash<world::map::Tile>::operator()(const world::map::Tile &tile) const {
  const size_t kBitsPerByte = 8;
  const size_t kBitsWall = 6;
  const size_t kBitsFloor = sizeof(size_t) * kBitsPerByte - world::map::Tile::kWallCount * kBitsWall;

  const size_t kWallMask = (static_cast<size_t>(1) << kBitsWall) - 1;
  const size_t kFloorMask = (static_cast<size_t>(1) << kBitsFloor) - 1;

  size_t result = 0;
  result |= hash<world::map::FloorMaterialType>{}(tile.floor) & kFloorMask;

  for (size_t wall = 0; wall < world::map::Tile::kWallCount; ++wall) {
    result |= (hash<world::map::Wall>{}(tile.walls[wall]) & kWallMask) << (kBitsFloor + wall * kBitsWall);
  }

  return result;
}

}
