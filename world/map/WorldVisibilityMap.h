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
    /** Total visibility of position in range [0.0; `n`], where `n` is number of positions of view. */
    double visibility;
    /** Min distance to tile. */
    double distance;

    /** Creates default position info. */
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
   * Creates and calculates visibility map using different sourcas.
   * @param game_config Const reference to game config.
   * @param map World map.
   * @param positions Positions of view.
   */
  WorldVisibilityMap(const config::GameConfig &game_config, const world::map::WorldMap &map,
                     const std::vector<util::Vector2<size_t>> &positions);

  /**
   * Returns info about given position.
   * @param position Position.
   */
  std::optional<PositionInfo> GetPositionInfo(const util::Vector2<size_t> &position);

 private:
  /** Size of map. */
  util::Vector2<size_t> map_size_;
  /** Positions of view. */
  std::vector<util::Vector2<size_t>> source_positions_;
  /** Result of calculation. */
  std::vector<PositionInfo> positions_;

  /**
   * Calculates position info for given position.
   * @param game_config Const reference to game config.
   * @param map World map.
   * @param source_position_index Index of source position.
   * @param position Position to calculate.
   */
  void CalculatePositionInfo(const config::GameConfig &game_config, const world::map::WorldMap &map,
                             size_t source_position_index, const util::Vector2<size_t> &position);

};

}
