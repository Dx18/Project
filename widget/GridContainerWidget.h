#pragma once

#include <vector>
#include <sstream>

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
   * equally between expandable cells (if there are any). If size of free space is not divisible by the number of
   * expandable cells, first cells get more space than the last. After that method fills result with calculated cell
   * sizes and returns true.
   * @param cells Cells.
   * @param max_size Max size.
   * @param result Result of calculation.
   */
  static bool ResolveLinearCells(const std::vector<LinearCell> &cells, size_t max_size, std::vector<size_t> &result);

};

template<typename RenderContext>
GridContainerWidget<RenderContext>::GridContainerWidget(const util::Vector2<size_t> &dimensions)
    : dimensions_(dimensions), widgets_(dimensions_.x * dimensions_.y) {

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

      result[j].min_size = std::max(result[i].min_size, min_size.x);
      result[j].expand = result[i].expand || expand.x;
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

  size_t free_space = max_size - sum_size;
  size_t min_space = free_space / expandable_count;
  size_t increased_count = free_space % expandable_count;

  size_t current_expandable = 0;
  for (const LinearCell &cell : cells) {
    if (cell.expand) {
      size_t additional_size = current_expandable < increased_count ? min_space + 1 : min_space;
      result.push_back(cell.min_size + additional_size);
      ++current_expandable;
    } else {
      result.push_back(cell.min_size);
    }
  }

  return true;
}

}
