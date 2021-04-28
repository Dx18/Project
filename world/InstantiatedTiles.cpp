#include "InstantiatedTiles.h"

namespace world {

const size_t InstantiatedTiles::kMissingTileID = 0;

InstantiatedTiles::InstantiatedTiles()
    : next_tile_id_(1), tiles_(), tile_ids_() {

}

TileID InstantiatedTiles::GetTileID(Tile tile) {
  auto iter = tile_ids_.find(tile);
  if (iter != tile_ids_.end()) {
    return iter->second;
  }

  TileID result = next_tile_id_;
  ++next_tile_id_;

  tiles_.insert({result, tile});
  tile_ids_.insert({std::move(tile), result});

  return result;
}

std::optional<Tile> InstantiatedTiles::GetTile(TileID tile_id) const {
  if (tile_id == kMissingTileID) {
    return {};
  }

  auto iter = tiles_.find(tile_id);
  if (iter != tiles_.end()) {
    return iter->second;
  }

  return {};
}

}
