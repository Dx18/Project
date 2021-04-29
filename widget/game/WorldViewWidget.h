#pragma once

#include "util/Math.h"
#include "widget/Widget.h"
#include "world/World.h"

namespace widget::game {

/**
 * Widget for world rendering.
 * @tparam Context Type with following associated types: `Context::RenderContext` (used to render widget),
 *                 `Context::ResourcesContext` (resources associated with context).
 */
template<typename Context>
class WorldViewWidget : public Widget<Context> {
 public:
  /**
   * Creates world rendering widget.
   * @param world Shared pointer to world to render.
   * @param camera_position Position of camera.
   * @param move_sensitivity Move sensitivity: how fast camera is moved. Exact interpretation depends on `Context`.
   */
  WorldViewWidget(std::shared_ptr<const world::World> world, const util::Vector2<double> &camera_position,
                  double move_sensitivity);

  [[nodiscard]] util::Vector2<size_t> MinSize(typename Context::Resources &resources) const override;
  void Render(typename Context::RenderContext &context, typename Context::Resources &resources) override;
  bool HandleInput(const frontend::Input &input) override;

 private:
  /** Shared pointer to world to render. */
  std::shared_ptr<const world::World> world_;
  /** Position of camera. */
  util::Vector2<double> camera_position_;
  /** Move sensitivity: how fast camera is moved. */
  double move_sensitivity_;

};

template<typename Context>
WorldViewWidget<Context>::WorldViewWidget(std::shared_ptr<const world::World> world,
                                          const util::Vector2<double> &camera_position,
                                          double move_sensitivity)
    : world_(std::move(world)), camera_position_(camera_position), move_sensitivity_(move_sensitivity) {

}

template<typename Context>
bool WorldViewWidget<Context>::HandleInput(const frontend::Input &input) {
  if (input.IsKey()) {
    bool handled = false;

    if (input.GetKey() == frontend::Key::kUp) {
      camera_position_.y -= move_sensitivity_;
      handled = true;
    } else if (input.GetKey() == frontend::Key::kRight) {
      camera_position_.x += move_sensitivity_;
      handled = true;
    } else if (input.GetKey() == frontend::Key::kDown) {
      camera_position_.y += move_sensitivity_;
      handled = true;
    } else if (input.GetKey() == frontend::Key::kLeft) {
      camera_position_.x -= move_sensitivity_;
      handled = true;
    }

    if (handled) {
      util::Vector2<size_t> map_size = world_->Map().Size();
      camera_position_.x = util::math::clamp(camera_position_.x, 0.0, static_cast<double>(map_size.x));
      camera_position_.y = util::math::clamp(camera_position_.y, 0.0, static_cast<double>(map_size.y));
    }

    return handled;
  }

  return false;
}

}
