#include "WorldRenderer.h"

namespace widget::terminal {

const CharData WorldRenderer::kUndefinedChar = CharData(
    '?', ColorPair(Color::kMagenta, Color::kBlack)
);

const size_t WorldRenderer::kTileSubdivision = 3;

void WorldRenderer::Render(const World &world, const util::Vector2<double> &camera_position,
                           bool pointed_tile_highlighted, const std::vector<bool> &navigation_tiles,
                           std::optional<size_t> selected_unit, IRenderSurfaceWrite &context,
                           TerminalResources &resources) const {
  util::Vector2<size_t> map_size = world.Map().Size();
  if (navigation_tiles.size() != map_size.x * map_size.y) {
    throw std::runtime_error("size of highlight map is incorrect");
  }

  RenderMap(world.Map(), camera_position, pointed_tile_highlighted, navigation_tiles, context, resources);
  RenderUnits(false, world.Entities(), camera_position, selected_unit, context, resources);
  RenderUnits(true, world.Entities(), camera_position, selected_unit, context, resources);
  RenderProjectiles(world.Entities(), camera_position, context, resources);
}

void WorldRenderer::RenderMap(const WorldMap &map, const util::Vector2<double> &camera_position,
                              bool pointed_tile_highlighted, const std::vector<bool> &navigation_tiles,
                              IRenderSurfaceWrite &context, TerminalResources &resources) const {
  auto tile_row = static_cast<ssize_t>(std::floor(camera_position.y));
  auto tile_column = static_cast<ssize_t>(std::floor(camera_position.x));

  util::Vector2<size_t> surface_size = context.Size();
  ssize_t tile_surface_row = static_cast<ssize_t>(surface_size.y) / 2 - static_cast<ssize_t>(std::floor(
      (camera_position.y - tile_row) * kTileSubdivision
  ));
  ssize_t tile_surface_column = static_cast<ssize_t>(surface_size.x) / 2 - static_cast<ssize_t>(std::floor(
      (camera_position.x - tile_column) * kTileSubdivision
  ));

  util::Vector2<size_t> map_size = map.Size();
  for (size_t row = 0; row < map_size.y; ++row) {
    for (size_t column = 0; column < map_size.x; ++column) {
      std::optional<Tile> tile = map.Get({column, row});
      if (!tile.has_value()) {
        continue;
      }

      ssize_t surface_row = tile_surface_row + (static_cast<ssize_t>(row) - tile_row) * kTileSubdivision;
      ssize_t surface_column = tile_surface_column + (static_cast<ssize_t>(column) - tile_column) * kTileSubdivision;

      RenderSurfaceBase texture = CreateTileTexture(*tile, resources);
      util::Vector2<size_t> texture_size = texture.Size();

      if (pointed_tile_highlighted && tile_row == row && tile_column == column) {
        RenderSurfaceBase pointed_tile_texture = resources.GetTexture("pointed_tile");
        for (size_t texture_row = 0; texture_row < texture_size.y; ++texture_row) {
          for (size_t texture_column = 0; texture_column < texture_size.x; ++texture_column) {
            CharData ch = pointed_tile_texture.Get({texture_column, texture_row});

            if (ch.color.foreground != Color::kBlack) {
              texture.Get({texture_column, texture_row}) = ch;
            }
          }
        }
      }

      for (size_t texture_row = 0; texture_row < texture_size.y; ++texture_row) {
        for (size_t texture_column = 0; texture_column < texture_size.x; ++texture_column) {
          ssize_t final_surface_row = surface_row + static_cast<ssize_t>(texture_row);
          ssize_t final_surface_column = surface_column + static_cast<ssize_t>(texture_column);
          if (final_surface_row >= 0 && final_surface_row < surface_size.y
              && final_surface_column >= 0 && final_surface_column < surface_size.x) {
            CharData ch = texture.Get({texture_column, texture_row});
            if (navigation_tiles[row * map_size.x + column]) {
              ch.color = ch.color.Inverted();
            }

            context.Get({
                            static_cast<size_t>(final_surface_column),
                            static_cast<size_t>(final_surface_row)
                        }) = ch;
          }
        }
      }
    }
  }
}

void WorldRenderer::RenderUnits(bool enemy, const world::entities::WorldEntities &entities,
                                const util::Vector2<double> &camera_position, std::optional<size_t> selected_unit,
                                IRenderSurfaceWrite &context, TerminalResources &resources) const {
  auto tile_row = static_cast<ssize_t>(std::floor(camera_position.y));
  auto tile_column = static_cast<ssize_t>(std::floor(camera_position.x));

  util::Vector2<size_t> surface_size = context.Size();
  ssize_t tile_surface_row = static_cast<ssize_t>(surface_size.y) / 2 - static_cast<ssize_t>(std::floor(
      (camera_position.y - tile_row) * kTileSubdivision
  ));
  ssize_t tile_surface_column = static_cast<ssize_t>(surface_size.x) / 2 - static_cast<ssize_t>(std::floor(
      (camera_position.x - tile_column) * kTileSubdivision
  ));

  CharData texture = GetOnePixelTexture(enemy ? "enemy_unit" : "player_unit", resources);

  const unit::Unit *selected_unit_ptr = selected_unit.has_value() && entities.UnitExists(*selected_unit)
                                        ? &entities.GetUnit(*selected_unit)
                                        : nullptr;

  for (const std::unique_ptr<unit::Unit> &unit : (enemy ? entities.EnemyUnits() : entities.PlayerUnits())) {
    util::Vector3<double> position = unit->Position();

    ssize_t surface_row = std::floor(tile_surface_row + (position.y - tile_row) * kTileSubdivision);
    ssize_t surface_column = std::floor(tile_surface_column + (position.x - tile_column) * kTileSubdivision);

    if (surface_row >= 0 && surface_row < surface_size.y
        && surface_column >= 0 && surface_column < surface_size.x) {
      CharData curr_texture = texture;
      if (unit.get() == selected_unit_ptr) {
        curr_texture.color = curr_texture.color.Inverted();
      }

      context.Get({
                      static_cast<size_t>(surface_column),
                      static_cast<size_t>(surface_row)
                  }) = curr_texture;
    }
  }
}

void WorldRenderer::RenderProjectiles(const world::entities::WorldEntities &entities,
                                      const util::Vector2<double> &camera_position, IRenderSurfaceWrite &context,
                                      TerminalResources &resources) const {
  auto tile_row = static_cast<ssize_t>(std::floor(camera_position.y));
  auto tile_column = static_cast<ssize_t>(std::floor(camera_position.x));

  util::Vector2<size_t> surface_size = context.Size();
  ssize_t tile_surface_row = static_cast<ssize_t>(surface_size.y) / 2 - static_cast<ssize_t>(std::floor(
      (camera_position.y - tile_row) * kTileSubdivision
  ));
  ssize_t tile_surface_column = static_cast<ssize_t>(surface_size.x) / 2 - static_cast<ssize_t>(std::floor(
      (camera_position.x - tile_column) * kTileSubdivision
  ));

  CharData texture = GetOnePixelTexture("projectile", resources);

  for (const world::entities::Projectile &projectile : entities.Projectiles()) {
    util::Vector3<double> position = projectile.CurrentPosition();

    ssize_t surface_row = std::floor(tile_surface_row + (position.y - tile_row) * kTileSubdivision);
    ssize_t surface_column = std::floor(tile_surface_column + (position.x - tile_column) * kTileSubdivision);

    if (surface_row >= 0 && surface_row < surface_size.y && surface_column >= 0 && surface_column < surface_size.x) {
      context.Get({
                      static_cast<size_t>(surface_column),
                      static_cast<size_t>(surface_row)
                  }) = texture;
    }
  }
}

RenderSurfaceBase WorldRenderer::CreateTileTexture(const Tile &tile, TerminalResources &resources) const {
  RenderSurfaceBase texture({kTileSubdivision, kTileSubdivision}, kUndefinedChar);
  texture.Get({0, 0}) = CornerChar(tile, Tile::kWallLeft, Tile::kWallUp, resources);
  texture.Get({1, 0}) = WallChar(tile, Tile::kWallUp, resources);
  texture.Get({2, 0}) = CornerChar(tile, Tile::kWallUp, Tile::kWallRight, resources);
  texture.Get({2, 1}) = WallChar(tile, Tile::kWallRight, resources);
  texture.Get({2, 2}) = CornerChar(tile, Tile::kWallRight, Tile::kWallDown, resources);
  texture.Get({1, 2}) = WallChar(tile, Tile::kWallDown, resources);
  texture.Get({0, 2}) = CornerChar(tile, Tile::kWallDown, Tile::kWallLeft, resources);
  texture.Get({0, 1}) = WallChar(tile, Tile::kWallLeft, resources);
  texture.Get({1, 1}) = FloorChar(tile, resources);
  return texture;
}

CharData WorldRenderer::GetOnePixelTexture(const std::string &name, TerminalResources &resources) const {
  const RenderSurfaceBase &texture = resources.GetTexture(name);

  util::Vector2<size_t> texture_size = texture.Size();

  if (texture_size.x != 1 || texture_size.y != 1) {
    return kUndefinedChar;
  }

  return texture.Get({0, 0});
}

CharData WorldRenderer::FloorChar(const Tile &tile, TerminalResources &resources) const {
  try {
    std::stringstream texture_name;
    texture_name << "tile_" << kFloorMaterial[tile.floor].name;
    return GetOnePixelTexture(texture_name.str(), resources);
  } catch (std::runtime_error &) {
    return kUndefinedChar;
  }
}

CharData WorldRenderer::WallChar(const Tile &tile, size_t orientation, TerminalResources &resources) const {
  if (tile.walls[orientation].form == WallForm::kNoWall) {
    return FloorChar(tile, resources);
  } else if (tile.walls[orientation].form == WallForm::kHalf) {
    return GetOnePixelTexture("tile_wall_half", resources);
  } else if (tile.walls[orientation].form == WallForm::kFull) {
    return GetOnePixelTexture("tile_wall_full", resources);
  } else {
    return kUndefinedChar;
  }
}

CharData WorldRenderer::CornerChar(const Tile &tile, size_t orientation1, size_t orientation2,
                                   TerminalResources &resources) const {
  if (tile.walls[orientation1].form >= tile.walls[orientation2].form) {
    return WallChar(tile, orientation1, resources);
  } else {
    return WallChar(tile, orientation2, resources);
  }
}

}
