#pragma once

#include <queue>

#include "WorldMap.h"

namespace world::map {

/** Contains result of BFS on world map starting from given position. */
class WorldMovementMap {
 public:
  /** Information about position on world map. */
  struct PositionInfo {
    /** Position. */
    util::Vector2<size_t> position;
    /** Distance to this position from fixed point. */
    long long distance;
    /**
     * If `distance` is zero, then it's equal to `position`. Otherwise it's equal to next point on path to start
     * position.
     */
    util::Vector2<size_t> next_to_start;

    /**
     * Creates position information.
     * @param position Position.
     * @param distance Distance to this position.
     * @param next_to_start Parent vertex in BFS, or `position`, if there is no parent.
     */
    PositionInfo(util::Vector2<size_t> position, long long distance, util::Vector2<size_t> next_to_start);

  };

  /**
   * Performs BFS and stores its result.
   * @param map World map.
   * @param start_position Start position.
   * @param distance_cap Optional max distance bound. If specified, then positions with distance greater than this
   *                     value are not stored in result.
   */
  WorldMovementMap(const WorldMap &map, const util::Vector2<size_t> &start_position,
                   std::optional<size_t> distance_cap);

  /** Returns array of reachable positions with use of distance cap if it was given in constructor. */
  std::vector<PositionInfo> AvailablePositions() const;
  /**
   * Returns positions on path from start position passed in constructor to given end position.
   * @param end_position End position.
   */
  std::optional<std::vector<PositionInfo>> Path(util::Vector2<size_t> end_position) const;

 private:
  /** Size of map. */
  util::Vector2<size_t> map_size_;
  /** Start position. */
  util::Vector2<size_t> start_position_;
  /** Result of BFS. */
  std::vector<std::optional<PositionInfo>> positions_;

};

}
