#pragma once

namespace world {

/** Form of wall. */
enum WallForm {
  /** No wall. Cannot be used as cover by units. */
  kNoWall,
  /** Half height wall. Can be used as average cover by units. */
  kHalf,
  /** Full height wall. Can be used as good cover by units. */
  kFull
};

}
