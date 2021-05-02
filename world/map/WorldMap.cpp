#include "WorldMap.h"

namespace world::map {

WorldMap::WorldMap(const util::Vector2<size_t> &size)
    : size_(size), data_(size.x * size.y, InstantiatedTiles::kMissingTileID), tiles_() {

}

const util::Vector2<size_t> &WorldMap::Size() const {
  return size_;
}

util::Rectangle<size_t> WorldMap::Rectangle() const {
  return {0, 0, size_.x, size_.y};
}

std::optional<Tile> WorldMap::Get(const util::Vector2<size_t> &position) const {
  CheckIfContainsPoint(position);
  return tiles_.GetTile(data_[GetTileIndex(position)]);
}

void WorldMap::Set(const util::Vector2<size_t> &position, Tile tile) {
  CheckIfContainsPoint(position);
  data_[GetTileIndex(position)] = tiles_.GetTileID(tile);
}

util::Vector2<size_t> WorldMap::TilePositionClamped(const util::Vector2<double> &position) const {
  size_t row = 0;
  if (position.y > 0.0) {
    row = std::min(static_cast<size_t>(std::floor(position.y)), size_.y - 1);
  }
  size_t column = 0;
  if (position.x > 0.0) {
    row = std::min(static_cast<size_t>(std::floor(position.x)), size_.x - 1);
  }

  return {column, row};
}

void WorldMap::CheckIfContainsPoint(const util::Vector2<size_t> &point) const {
  util::Rectangle<size_t> current_rectangle = Rectangle();
  if (!current_rectangle.ContainsPoint(point)) {
    std::stringstream message;
    message << "world map with rectangle " << current_rectangle << " does not contain given point " << point;
    throw std::runtime_error(message.str());
  }
}

size_t WorldMap::GetTileIndex(const util::Vector2<size_t> &position) const {
  return position.y * size_.x + position.x;
}

}
