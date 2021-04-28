#pragma once

#include <unordered_map>

#include "Tile.h"
#include "TileID.h"

namespace world {

/** Currently instantiated tiles in world. */
class InstantiatedTiles {
 public:
  /** Reserved tile ID representing missing tile. */
  static const TileID kMissingTileID;

  /** Creates instantiated tiles without any tiles. */
  InstantiatedTiles();

  /**
   * Returns tile ID of given tile. If given tile was not registered then this method registers it.
   * @param tile Tile.
   */
  TileID GetTileID(Tile tile);
  /**
   * Returns tile by given ID. May return no value if:
   * 1. Given tile ID was not registered;
   * 2. Given tile ID represents missing tile.
   * @param tile_id ID of tile to get.
   */
  std::optional<Tile> GetTile(TileID tile_id) const;

 private:
  /** Tile ID counter. */
  TileID next_tile_id_;
  /** Instantiated tiles: used to get tile by tile ID. */
  std::unordered_map<TileID, Tile> tiles_;
  /** Instantiated tiles: used to get tile ID by tile. */
  std::unordered_map<Tile, TileID> tile_ids_;

};

}
