#pragma once

#include <unordered_set>

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

  /** Returns current camera position. */
  [[nodiscard]] util::Vector2<double> CameraPosition() const;
  /**
   * Sets camera position.
   * @param camera_position Camera position to set.
   */
  void SetCameraPosition(const util::Vector2<double> &camera_position);

  /**
   * Sets whether tile right under camera is highlighted or not.
   * @param highlighted True if tile should be highlighted.
   */
  void SetPointedTileHighlighted(bool highlighted);

  /**
   * Sets tiles displayed as navigation tiles: tiles where unit can travel.
   * @param tiles Positions of tiles.
   */
  void SetNavigationTiles(const std::vector<util::Vector2<size_t>> &tiles);

  /**
   * Sets unit highlighted on render. Method checks unit ID of correctness and throws `std::runtime_error` if it is not
   * correct.
   * @param unit_id ID of unit.
   */
  void SetSelectedUnit(size_t unit_id);
  /** Resets selected unit. */
  void ResetSelectedUnit();

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
  std::vector<util::Vector2<size_t>> highlighted_tiles_;
  /** True if pointed tile should be highlighted. */
  bool pointed_tile_highlighted_;
  /** Navigation tiles. */
  std::vector<bool> navigation_tiles_;
  /** Currently selected unit which will be highlighted on render. */
  std::optional<size_t> selected_unit_;

};

template<typename Context>
WorldViewWidget<Context>::WorldViewWidget(std::shared_ptr<const world::World> world,
                                          const util::Vector2<double> &camera_position,
                                          double move_sensitivity)
    : world_(std::move(world)), camera_position_(camera_position), move_sensitivity_(move_sensitivity),
      pointed_tile_highlighted_(false), highlighted_tiles_(), navigation_tiles_(), selected_unit_() {
  util::Vector2<size_t> map_size = world_->Map().Size();
  navigation_tiles_.resize(map_size.x * map_size.y, false);
}

template<typename Context>
util::Vector2<double> WorldViewWidget<Context>::CameraPosition() const {
  return camera_position_;
}

template<typename Context>
void WorldViewWidget<Context>::SetCameraPosition(const util::Vector2<double> &camera_position) {
  camera_position_ = camera_position;
  util::Vector2<size_t> map_size = world_->Map().Size();
  camera_position_.x = util::math::clamp(camera_position_.x, 0.0, static_cast<double>(map_size.x));
  camera_position_.y = util::math::clamp(camera_position_.y, 0.0, static_cast<double>(map_size.y));
}

template<typename Context>
void WorldViewWidget<Context>::SetPointedTileHighlighted(bool highlighted) {
  pointed_tile_highlighted_ = highlighted;
}

template<typename Context>
void WorldViewWidget<Context>::SetNavigationTiles(const std::vector<util::Vector2<size_t>> &tiles) {
  for (const util::Vector2<size_t> &position : tiles) {
    world_->Map().CheckIfContainsPoint(position);
  }

  util::Vector2<size_t> map_size = world_->Map().Size();
  for (const util::Vector2<size_t> &position : highlighted_tiles_) {
    navigation_tiles_[position.y * map_size.x + position.x] = false;
  }

  highlighted_tiles_ = tiles;

  for (const util::Vector2<size_t> &position : highlighted_tiles_) {
    navigation_tiles_[position.y * map_size.x + position.x] = true;
  }
}

template<typename Context>
void WorldViewWidget<Context>::SetSelectedUnit(size_t unit_id) {
  const unit::Unit &unit = world_->Entities().GetUnit(unit_id);
  selected_unit_ = unit_id;
}

template<typename Context>
void WorldViewWidget<Context>::ResetSelectedUnit() {
  selected_unit_ = {};
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
