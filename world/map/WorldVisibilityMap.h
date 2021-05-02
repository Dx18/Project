#pragma once

#include <cmath>

#include "util/Vector.h"
#include "config/GameConfig.h"

#include "WorldMap.h"

namespace world::map {

/** Map of tile visibility from fixed point. */
class WorldVisibilityMap {
 public:
  /** Information about position on world map. */
  struct PositionInfo {
    /** Position. */
    util::Vector2<size_t> position;
    /** Visibility of tile in range [0.0; 1.0]. */
    double visibility;
    /** Distance to tile. */
    double distance;

    /** Creates default zero-initialized position info. */
    PositionInfo();
    /**
     * Creates position info.
     * @param _position Position.
     * @param _visibility Visibility.
     * @param _distance Distance.
     */
    PositionInfo(util::Vector2<size_t> _position, double _visibility, double _distance);

  };

  /**
   * Creates and calculates visibility map.
   * @param game_config Const reference to game config.
   * @param map World map.
   * @param position Position of view.
   */
  WorldVisibilityMap(const config::GameConfig &game_config, const world::map::WorldMap &map,
                     const util::Vector2<size_t> &position);

  /**
   * Returns info about given position.
   * @param position Position.
   */
  std::optional<PositionInfo> GetPositionInfo(const util::Vector2<size_t> &position);

 private:
  /** Size of map. */
  util::Vector2<size_t> map_size_;
  /** Position of view. */
  util::Vector2<size_t> position_;
  /** Result of calculation. */
  std::vector<PositionInfo> positions_;

  /**
   * Calculates position info for given position.
   * @param game_config Const reference to game config.
   * @param map World map.
   * @param position Position to calculate.
   */
  PositionInfo CalculatePositionInfo(const config::GameConfig &game_config, const world::map::WorldMap &map,
                                     const util::Vector2<size_t> position);

};

}
