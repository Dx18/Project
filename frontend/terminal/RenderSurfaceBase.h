#pragma once

#include <vector>

#include "IRenderSurfaceWrite.h"

namespace frontend::terminal {

/** Base render surface. Contains characters data to draw. */
class RenderSurfaceBase : public IRenderSurfaceWrite {
 public:
  /** Creates zero-sized render surface. */
  RenderSurfaceBase();
  /**
   * Creates render surface with given size.
   * @param size Size (X coordinate is width, Y coordinate is height).
   * @param char_data Character data to set.
   */
  RenderSurfaceBase(const util::Vector2<size_t> &size, const CharData &char_data);

  /**
   * Updates size of surface and sets all character data equal to given.
   * @param new_size New size.
   * @param char_data Character data to set.
   */
  void ResizeClear(const util::Vector2<size_t> &new_size, const CharData &char_data);

  [[nodiscard]] util::Vector2<size_t> Size() const override;
  [[nodiscard]] const CharData &Get(const util::Vector2<size_t> &position) const override;
  CharData &Get(const util::Vector2<size_t> &position) override;

 private:
  /** Data of surface. */
  std::vector<CharData> data_;
  /** Size of surface. */
  util::Vector2<size_t> size_;

  /**
   * Returns index of character data at given position at data array. Does not check `position` for bounds.
   * @param position Position.
   */
  [[nodiscard]] size_t GetCharIndex(const util::Vector2<size_t> &position) const;

};

}
