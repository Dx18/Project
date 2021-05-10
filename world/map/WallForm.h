#pragma once

namespace world::map {

/** Form of wall. */
enum WallForm {
  /** No wall. Cannot be used as cover by units. */
  kNoWall = 0,
  /** Half height wall. Can be used as average cover by units. */
  kHalf = 1,
  /** Full height wall. Can be used as good cover by units. */
  kFull = 2
};

}
