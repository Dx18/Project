#include "WorldMovementMap.h"

namespace world::map {

WorldMovementMap::PositionInfo::PositionInfo(util::Vector2<size_t> position, long long distance,
                                             util::Vector2<size_t> next_to_start) {

}

WorldMovementMap::WorldMovementMap(const WorldMap &map, const util::Vector2<size_t> &start_position,
                                   std::optional<size_t> distance_cap)
    : map_size_(map.Size()), start_position_(start_position), positions_(map_size_.x * map_size_.y) {
  struct Transition {
    util::Vector2<ssize_t> delta;
    size_t wall_current;
    size_t wall_next;
  };

  static const std::array<Transition, 4> kTransitions = {
      {{{-1, 0}, Tile::kWallUp, Tile::kWallDown},
       {{0, 1}, Tile::kWallRight, Tile::kWallLeft},
       {{1, 0}, Tile::kWallDown, Tile::kWallUp},
       {{0, -1}, Tile::kWallLeft, Tile::kWallRight}}
  };

  map.CheckIfContainsPoint(start_position);

  std::queue<util::Vector2<size_t>> position_queue;
  position_queue.push(start_position);
  positions_[start_position.y * map_size_.x + start_position.x]
      = PositionInfo(start_position, 0, start_position);

  while (!position_queue.empty()) {
    util::Vector2<size_t> curr = position_queue.front();
    position_queue.pop();

    for (const Transition &transition : kTransitions) {
      ssize_t next_row = static_cast<ssize_t>(curr.y) + transition.delta.y;
      ssize_t next_column = static_cast<ssize_t>(curr.x) + transition.delta.x;

      if (next_row >= 0 && next_row < map_size_.y && next_column >= 0 && next_column < map_size_.x
          && !positions_[next_row * map_size_.x + next_column].has_value()) {
        long long distance = positions_[curr.y * map_size_.x + curr.x]->distance + 1;
        if (distance_cap.has_value() && distance >= *distance_cap) {
          continue;
        }

        util::Vector2<size_t> next = {static_cast<size_t>(next_row), static_cast<size_t>(next_column)};

        position_queue.push(next);
        positions_[next.y * map_size_.x + next.x] = PositionInfo(next, distance, curr);
      }
    }
  }
}

std::vector<WorldMovementMap::PositionInfo> WorldMovementMap::AvailablePositions() const {
  std::vector<PositionInfo> result;
  for (const std::optional<PositionInfo> &position : positions_) {
    if (position.has_value()) {
      result.push_back(*position);
    }
  }
  return result;
}

std::optional<std::vector<WorldMovementMap::PositionInfo>> WorldMovementMap::Path(util::Vector2<size_t> end_position) const {
  if (end_position.y >= map_size_.y || end_position.x >= map_size_.x
      || positions_[end_position.y * map_size_.x + end_position.x]) {
    return {};
  }

  std::vector<WorldMovementMap::PositionInfo> result;
  util::Vector2<size_t> curr = end_position;
  while (curr.x != start_position_.x || curr.y != start_position_.y) {
    PositionInfo position = *positions_[curr.y * map_size_.x + curr.x];
    result.push_back(position);
    curr = position.next_to_start;
  }

  result.push_back(*positions_[curr.y * map_size_.x + curr.x]);
  std::reverse(result.begin(), result.end());
  return result;
}

}
