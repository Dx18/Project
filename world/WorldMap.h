#pragma once

#include <vector>
#include <sstream>

#include "util/Vector.h"
#include "util/Rectangle.h"

#include "InstantiatedTiles.h"

namespace world {

/** Tiled world map. */
class WorldMap {
 public:
  /**
   * Creates world map with given size.
   * @param size Size of world map in tiles.
   */
  explicit WorldMap(const util::Vector2<size_t> &size);

  /** Returns size of world map. */
  const util::Vector2<size_t> &Size() const;
  /** Returns rectangle containing world map. */
  util::Rectangle<size_t> Rectangle() const;

  /**
   * Returns tile at given position. Returns no value if tile is missing.
   * @param position Position to get tile from.
   */
  std::optional<Tile> Get(const util::Vector2<size_t> &position) const;
  /**
   * Assigns tile at given position.
   * @param position Position.
   * @param tile Tile to set.
   */
  void Set(const util::Vector2<size_t> &position, Tile tile);

 private:
  /** Size of world map. */
  util::Vector2<size_t> size_;
  /** World tiles arranged by row, and then by column. */
  std::vector<TileID> data_;
  /** Instantiated tiles. */
  InstantiatedTiles tiles_;

  /**
   * Checks if world map contains given point. Throws `std::runtime_error` if check is failed.
   * @param point Point to check.
   */
  void CheckIfContainsPoint(const util::Vector2<size_t> &point) const;
  /**
   * Returns index of tile in internal data array. Does not perform any bound checks.
   * @param position Position of tile.
   */
  size_t GetTileIndex(const util::Vector2<size_t> &position) const;

};

}
