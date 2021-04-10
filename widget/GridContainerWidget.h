#pragma once

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

};

template<typename RenderContext>
GridContainerWidget<RenderContext>::GridContainerWidget(const util::Vector2<size_t> &dimensions)
    : dimensions_(dimensions), widgets_() {

}

template<typename RenderContext>
const util::Vector2<size_t> &GridContainerWidget<RenderContext>::Dimensions() const {
  return dimensions_;
}

template<typename RenderContext>
const typename GridContainerWidget<RenderContext>::WidgetPtr &
GridContainerWidget<RenderContext>::Get(const util::Vector2<size_t> &position) const {
  CheckIfContainsSlot(position);
  return widgets_[GetWidgetIndex(position)];
}

template<typename RenderContext>
void GridContainerWidget<RenderContext>::Set(const util::Vector2<size_t> &position, const WidgetPtr &widget) {
  CheckIfContainsSlot(position);
  widgets_[GetWidgetIndex(position)] = widget;
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

}
