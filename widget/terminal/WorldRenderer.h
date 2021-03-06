#pragma once

#include <cmath>

#include "frontend/terminal/IRenderSurfaceWrite.h"
#include "frontend/terminal/TerminalResources.h"
#include "world/World.h"
#include "world/map/FloorMaterial.h"

namespace widget::terminal {

using namespace frontend::terminal;
using namespace world;
using namespace world::map;

/** World renderer for terminal frontend. */
class WorldRenderer {
 public:
  /**
   * Renders world. Throws `std::runtime_error` if size of given navigation map is incorrect.
   * @param world World to render.
   * @param camera_position Camera position: tile with this position will be rendered in the middle of surface.
   * @param pointed_tile_highlighted Should pointed tile be highlighted.
   * @param navigation_tiles Map of navigation tiles. Size must be equal to product of world map dimensions.
   * @param selected_unit Optional unit highlighted on render.
   * @param context Surface for rendering.
   * @param resources Terminal resources.
   */
  void Render(const World &world, const util::Vector2<double> &camera_position, bool pointed_tile_highlighted,
              const std::vector<bool> &navigation_tiles, std::optional<size_t> selected_unit,
              IRenderSurfaceWrite &context, TerminalResources &resources) const;

 private:
  /** Char used for textures. */
  static const CharData kUndefinedChar;
  /** Subdivision of tiles: height and width of each tile in characters. */
  static const size_t kTileSubdivision;

  /**
   * Renders world map. Size of highlight map is not checked.
   * @param map World map to render.
   * @param camera_position Camera position: tile with this position will be rendered in the middle of surface.
   * @param pointed_tile_highlighted Should pointed tile be highlighted.
   * @param navigation_tiles Map of navigation tiles.
   * @param context Surface for rendering.
   * @param resources Terminal resources.
   */
  void RenderMap(const WorldMap &map, const util::Vector2<double> &camera_position, bool pointed_tile_highlighted,
                 const std::vector<bool> &navigation_tiles, IRenderSurfaceWrite &context,
                 TerminalResources &resources) const;
  /**
   * Renders units.
   * @param enemy Are given units belonging to enemy or not.
   * @param entities World entities.
   * @param camera_position Camera position.
   * @param selected_unit Optional unit highlighted on render.
   * @param context Surface for rendering.
   * @param resources Terminal resources.
   */
  void RenderUnits(bool enemy, const world::entities::WorldEntities &entities,
                   const util::Vector2<double> &camera_position, std::optional<size_t> selected_unit,
                   IRenderSurfaceWrite &context, TerminalResources &resources) const;

  /**
   * Renders projectiles.
   * @param entities World entities.
   * @param camera_position Camera position.
   * @param context Surface for rendering.
   * @param resources Terminal resources.
   */
  void RenderProjectiles(const world::entities::WorldEntities &entities, const util::Vector2<double> &camera_position,
                         IRenderSurfaceWrite &context, TerminalResources &resources) const;

  /**
   * Creates new texture and renders tile to it.
   * @param tile Tile to render.
   * @param resources Terminal resources.
   */
  RenderSurfaceBase CreateTileTexture(const Tile &tile, TerminalResources &resources) const;

  /**
   * Returns one-pixel texture from resources. If texture does not exist or its size is not 1x1, then method returns
   * `WorldRenderer::kUndefinedChar`.
   * @param name Name of texture.
   * @param resources Terminal resources.
   */
  CharData GetOnePixelTexture(const std::string &name, TerminalResources &resources) const;

  /**
   * Returns character representing floor. Returns `WorldRenderer::kUndefinedChar` if required character was not found.
   * @param tile Tile.
   * @param resources Terminal resources.
   */
  CharData FloorChar(const Tile &tile, TerminalResources &resources) const;
  /**
   * Returns character representing wall. Returns `WorldRenderer::kUndefinedChar` if required character was not found.
   * Wall orientation must have one of the following values: `Tile::kWallUp`, `Tile::kWallRight`, `Tile::kWallDown`,
   * `Tile::kWallLeft`. Method does not check wall orientation.
   * @param tile Tile.
   * @param orientation Orientation of wall.
   * @param resources Terminal resources.
   */
  CharData WallChar(const Tile &tile, size_t orientation, TerminalResources &resources) const;
  /**
   * Returns character representing corner. Returns `WorldRenderer::kUndefinedChar` if required character was not found.
   * Wall orientations must have the following values: `Tile::kWallUp`, `Tile::kWallRight`, `Tile::kWallDown`,
   * `Tile::kWallLeft`. Wall orientations must be "neighbours": not similar and not opposite. Method does not check
   * wall orientations.
   * @param tile Tile.
   * @param orientation1 Orientation of the first wall.
   * @param orientation2 Orientation of the second wall.
   * @param resources Terminal resources.
   */
  CharData CornerChar(const Tile &tile, size_t orientation1, size_t orientation2, TerminalResources &resources) const;

};

}
