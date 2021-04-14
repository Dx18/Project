#pragma once

#include <vector>
#include <sstream>
#include <algorithm>
#include <cassert>

#include "util/Rectangle.h"

#include "Widget.h"

namespace widget {

/**
 * Widget containing set of widgets arranged as table.
 * @tparam RenderContext Context used to render widget.
 */
template<typename RenderContext>
class GridContainerWidget : public Widget<RenderContext> {
 private:
  using WidgetType = Widget<RenderContext>;
  using WidgetPtr = std::shared_ptr<WidgetType>;

 public:
  /**
   * Creates grid container with given dimensions.
   * @param dimensions Vector with X coordinate determining number of columns and Y coordinate determining number of
   *                   rows in grid.
   */
  explicit GridContainerWidget(const util::Vector2<size_t> &dimensions);

  /** Returns dimensions of grid container. */
  [[nodiscard]] const util::Vector2<size_t> &Dimensions() const;

  /**
   * Returns pointer to widget at given slot using its position. Throws `std::runtime_error` if given position is not
   * in valid range (if X coordinate is greater or equal to X dimension or Y coordinate is greater or equal to Y
   * dimension).
   * @param position Position of slot.
   */
  [[nodiscard]] const WidgetPtr &Get(const util::Vector2<size_t> &position) const;
  /**
   * Sets widget at given slot using its position. Throws `std::runtime_error` if given position is not in valid range
   * (if X coordinate is greater or equal to X dimension or Y coordinate is greater or equal to Y dimension).
   * @param position Position of slot.
   * @param widget Widget to set.
   */
  void Set(const util::Vector2<size_t> &position, const WidgetPtr &widget);

  /** Returns true if separators between cells should be rendered. */
  [[nodiscard]] bool RenderSeparators() const;
  /** Sets separator rendering. */
  void SetRenderSeparators(bool render_separators);

  /**
   * Returns min size of grid container based on min sizes of contained widgets. If row (column) does not contain any
   * widgets its height (width) is considered as 0.
   */
  [[nodiscard]] util::Vector2<size_t> MinSize() const override;
  void Render(RenderContext &context) override;

 private:
  /** Dimensions of grid. */
  util::Vector2<size_t> dimensions_;
  /** Widgets. */
  std::vector<WidgetPtr> widgets_;
  /** True if separators between grid cells should be rendered. */
  bool render_separators_;

  /**
   * Checks if current grid contains slot with given position. Throws `std::runtime_error` if given position is not in
   * valid range (if X coordinate is greater or equal to X dimension or Y coordinate is greater or equal to Y
   * dimension).
   * @param position Position of slot.
   */
  void CheckIfContainsSlot(const util::Vector2<size_t> &position) const;
  /**
   * Returns index of slot at given position. Does not check position for validity, if position is invalid, then result
   * is undefined.
   * @param position Position of slot.
   */
  [[nodiscard]] size_t GetSlotIndex(const util::Vector2<size_t> &position) const;

  /** Structure used to pass parameters to static method `ResolveLinearCells(...)`. */
  struct LinearCell {
    /** Min size of cell. */
    size_t min_size;
    /** Should cell be expanded. */
    bool expand;
  };

  /** Creates linear cells corresponding to rows. */
  std::vector<LinearCell> CreateRowCells() const;
  /** Creates linear cells corresponding to columns. */
  std::vector<LinearCell> CreateColumnCells() const;

  /**
   * Method used to calculate optimal sizes of "cells" (rows or columns). The result is stored in `result`. Each cell
   * has min size and expanding preference. If current sum size of cells is greater than `max_size`, method fills
   * `result` until it's sum is less or equal to `max_size` and returns false. Otherwise, method distributes free space
   * between expandable cells using following algorithm.
   *
   * Let `s_1 <= s_2 <= ... <= s_n` - sizes of expandable cells, `S_k = s_1 + ... + s_k`, `f` - amount of free space.
   * Let `k` is max number `k' = 1, ... n`, such as `S_k + f >= k * s_k`. Let `s'_1 = s'_2 = ... s'_k = s_k`,
   * `s'_i = s_i` for `i = k + 1, ... n`. Let `f' = S_k + f - k * s_k`. Let `x = f' div k`, `y = f' mod k`, where `div`
   * is integer division. Let `r_i = s'_i + x` for `i = 1, ... k - y`, `r_i = s'_i + x + 1` for `i = k - y + 1, ... k`,
   * `r_i = s'_i` for `i = k + 1, ... n`. `r_1, r_2, ... r_n` - fixed sizes of cells.
   *
   * After that method fills result with calculated cell sizes and returns true.
   * @param cells Cells.
   * @param max_size Max size.
   * @param result Result of calculation.
   */
  static bool ResolveLinearCells(const std::vector<LinearCell> &cells, size_t max_size, std::vector<size_t> &result);

};

/** Alias for shared pointer to grid container widget. */
template<typename RenderContext>
using GridContainerWidgetPtr = std::shared_ptr<GridContainerWidget<RenderContext>>;

template<typename RenderContext>
GridContainerWidget<RenderContext>::GridContainerWidget(const util::Vector2<size_t> &dimensions)
    : dimensions_(dimensions), widgets_(dimensions_.x * dimensions_.y), render_separators_(false) {

}

template<typename RenderContext>
const util::Vector2<size_t> &GridContainerWidget<RenderContext>::Dimensions() const {
  return dimensions_;
}

template<typename RenderContext>
const typename GridContainerWidget<RenderContext>::WidgetPtr &
GridContainerWidget<RenderContext>::Get(const util::Vector2<size_t> &position) const {
  CheckIfContainsSlot(position);
  return widgets_[GetSlotIndex(position)];
}

template<typename RenderContext>
void GridContainerWidget<RenderContext>::Set(const util::Vector2<size_t> &position, const WidgetPtr &widget) {
  CheckIfContainsSlot(position);
  widgets_[GetSlotIndex(position)] = widget;
}

template<typename RenderContext>
bool GridContainerWidget<RenderContext>::RenderSeparators() const {
  return render_separators_;
}

template<typename RenderContext>
void GridContainerWidget<RenderContext>::SetRenderSeparators(bool render_separators) {
  render_separators_ = render_separators;
}

template<typename RenderContext>
void GridContainerWidget<RenderContext>::CheckIfContainsSlot(const util::Vector2<size_t> &position) const {
  util::Rectangle<size_t> current_rectangle = {0, 0, dimensions_.x, dimensions_.y};
  if (!current_rectangle.ContainsPoint(position)) {
    std::stringstream message;
    message << "grid with dimensions " << dimensions_ << " does not contain given slot " << position;
    throw std::runtime_error(message.str());
  }
}

template<typename RenderContext>
size_t GridContainerWidget<RenderContext>::GetSlotIndex(const util::Vector2<size_t> &position) const {
  return position.y * dimensions_.x + position.x;
}

template<typename RenderContext>
std::vector<typename GridContainerWidget<RenderContext>::LinearCell>
GridContainerWidget<RenderContext>::CreateRowCells() const {
  std::vector<LinearCell> result(dimensions_.y, {0, false});
  for (size_t i = 0; i < dimensions_.y; ++i) {
    for (size_t j = 0; j < dimensions_.x; ++j) {
      const WidgetPtr &widget = widgets_[GetSlotIndex({j, i})];
      util::Vector2<size_t> min_size = widget ? widget->MinSize() : util::Vector2<size_t>{0, 0};
      util::Vector2<bool> expand = widget ? widget->PreferExpand() : util::Vector2<bool>{false, false};

      result[i].min_size = std::max(result[i].min_size, min_size.y);
      result[i].expand = result[i].expand || expand.y;
    }
  }
  return result;
}

template<typename RenderContext>
std::vector<typename GridContainerWidget<RenderContext>::LinearCell>
GridContainerWidget<RenderContext>::CreateColumnCells() const {
  std::vector<LinearCell> result(dimensions_.x, {0, false});
  for (size_t i = 0; i < dimensions_.y; ++i) {
    for (size_t j = 0; j < dimensions_.x; ++j) {
      const WidgetPtr &widget = widgets_[GetSlotIndex({j, i})];
      util::Vector2<size_t> min_size = widget ? widget->MinSize() : util::Vector2<size_t>{0, 0};
      util::Vector2<bool> expand = widget ? widget->PreferExpand() : util::Vector2<bool>{false, false};

      result[j].min_size = std::max(result[j].min_size, min_size.x);
      result[j].expand = result[j].expand || expand.x;
    }
  }
  return result;
}

template<typename RenderContext>
bool GridContainerWidget<RenderContext>::ResolveLinearCells(const std::vector<LinearCell> &cells, size_t max_size,
                                                            std::vector<size_t> &result) {
  size_t sum_size = 0;
  size_t expandable_count = 0;
  for (const LinearCell &cell : cells) {
    sum_size += cell.min_size;
    if (cell.expand) {
      ++expandable_count;
    }
  }

  if (sum_size > max_size || expandable_count == 0) {
    sum_size = 0;
    for (const LinearCell &cell : cells) {
      if (sum_size + cell.min_size > max_size) {
        break;
      }
      result.push_back(cell.min_size);
      sum_size += cell.min_size;
    }
    return sum_size <= max_size;
  }

  std::vector<size_t> expandable_indices;
  for (size_t i = 0; i < cells.size(); ++i) {
    if (cells[i].expand) {
      expandable_indices.push_back(i);
    }
  }

  std::sort(expandable_indices.begin(), expandable_indices.end(),
            [&cells](const size_t &index1, const size_t &index2) {
              const LinearCell &cell1 = cells[index1];
              const LinearCell &cell2 = cells[index2];

              return cell1.min_size < cell2.min_size
                  || (cell1.min_size == cell2.min_size && index1 < index2);
            });

  assert(expandable_indices.size() == expandable_count);

  size_t free_space = max_size - sum_size;
  size_t curr_sum = 0;
  size_t overflow_point = 0;
  for (; overflow_point < expandable_count; ++overflow_point) {
    curr_sum += cells[expandable_indices[overflow_point]].min_size;

    if (curr_sum + free_space < (overflow_point + 1) * cells[expandable_indices[overflow_point]].min_size) {
      curr_sum -= cells[expandable_indices[overflow_point]].min_size;
      break;
    }
  }

  std::vector<size_t> new_expandable_sizes(expandable_count);
  for (size_t i = 0; i < overflow_point; ++i) {
    new_expandable_sizes[i] = cells[expandable_indices[overflow_point - 1]].min_size;
  }
  for (size_t i = overflow_point; i < expandable_count; ++i) {
    new_expandable_sizes[i] = cells[expandable_indices[i]].min_size;
  }

  size_t new_free_space = curr_sum + free_space
      - overflow_point * cells[expandable_indices[overflow_point - 1]].min_size;

  for (size_t i = 0; i < overflow_point - new_free_space % overflow_point; ++i) {
    new_expandable_sizes[i] += new_free_space / overflow_point;
  }
  for (size_t i = overflow_point - new_free_space % overflow_point; i < overflow_point; ++i) {
    new_expandable_sizes[i] += new_free_space / overflow_point + 1;
  }

  for (const LinearCell &cell : cells) {
    result.push_back(cell.min_size);
  }
  for (size_t i = 0; i < expandable_count; ++i) {
    result[expandable_indices[i]] = new_expandable_sizes[i];
  }

  return true;
}

}
