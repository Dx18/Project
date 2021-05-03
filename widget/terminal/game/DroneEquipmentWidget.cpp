#include "widget/game/DroneEquipmentWidget.h"

#include <vector>

#include "frontend/terminal/RenderSurfaceRegion.h"

#include "../TerminalContext.h"

namespace widget::game {

using namespace frontend::terminal;

template<>
util::Vector2<size_t>
DroneEquipmentWidget<widget::terminal::TerminalContext>::MinSize(TerminalResources &resources) const {
  const size_t kCellHeight = 12;
  const size_t kCellWidth = 10;
  const size_t kGap = 1;
  const size_t kTopTextHeight = 2;
  return util::Vector2<size_t>{
      kCellWidth * kParameterCount + kGap * (kParameterCount - 1),
      kCellHeight + kTopTextHeight
  };
}

template<>
void DroneEquipmentWidget<widget::terminal::TerminalContext>::Render(IRenderSurfaceWrite &context,
                                                                     TerminalResources &resources) {
  const size_t kCellHeight = 12;
  const size_t kCellWidth = 10;
  const size_t kGap = 1;
  const size_t kTopTextHeight = 1;

  util::Vector2<size_t> size = context.Size();
  util::Vector2<size_t> min_size = MinSize(resources);

  if (size.x < min_size.x || size.y < min_size.y) {
    return;
  }

  std::array<std::array<std::string, kTopTextHeight>, kParameterCount> titles = {
      std::array<std::string, kTopTextHeight>{"  Weapon  "},
      std::array<std::string, kTopTextHeight>{"  Armor   "}
  };

  std::array<std::string, kWeaponClassInfo.size()> class_names;
  for (WeaponClassType weapon_class_type : kAvailableWeaponClasses) {
    class_names[weapon_class_type] = kWeaponClassInfo[weapon_class_type].name;
  }

  ColorPair normal_color(Color::kWhite, Color::kBlack);
  ColorPair selected_color(Color::kYellow, Color::kBlack);

  if (focused_) {
    selected_color = selected_color.Inverted();
  }

  size_t row_start = (size.y - min_size.y) / 2;
  size_t column_start = (size.x - min_size.x) / 2;

  RenderSurfaceRegion region(context,
                             util::Rectangle<size_t>{column_start, row_start, min_size.x, min_size.y});

  for (size_t cell = 0; cell < kParameterCount; ++cell) {
    ColorPair color = cell == current_parameter_ ? selected_color : normal_color;

    size_t curr_row_start = 0;
    size_t curr_column_start = cell * kCellWidth + (cell > 0 ? (cell - 1) * kGap : 0);

    RenderSurfaceRegion cell_region(region,
                                    util::Rectangle<size_t>{
                                        curr_column_start, curr_row_start, kCellWidth, min_size.y
                                    });

    for (size_t j = 0; j < kCellWidth; ++j) {
      for (size_t i = 0; i < kTopTextHeight; ++i) {
        cell_region.Get(util::Vector2<size_t>{j, i}) = CharData(titles[cell][i][j], color);
      }
    }

    for (size_t j = 1; j < kCellWidth - 1; ++j) {
      cell_region.Get(util::Vector2<size_t>{j, kTopTextHeight}) = CharData('-', color);
      cell_region.Get(util::Vector2<size_t>{j, kTopTextHeight + kCellHeight - 1}) = CharData('-', color);
    }
    for (size_t i = 1; i < kCellHeight - 1; ++i) {
      cell_region.Get(util::Vector2<size_t>{0, kTopTextHeight + i}) = CharData('|', color);
      cell_region.Get(util::Vector2<size_t>{kCellWidth - 1, kTopTextHeight + i}) = CharData('|', color);
    }
    for (size_t corner_row = 0; corner_row < 2; ++corner_row) {
      for (size_t corner_column = 0; corner_column < 2; ++corner_column) {
        cell_region.Get(util::Vector2<size_t>{
            (kCellWidth - 1) * corner_column,
            kTopTextHeight + (kCellHeight - 1) * corner_row
        }) = CharData('+', color);
      }
    }

    std::string text;
    if (cell == kWeaponParameterIndex) {
      if (weapon_.has_value()) {
        std::stringstream texture_name;
        texture_name << "drone_" << kWeaponClassInfo[weapon_.value()].name;
        cell_region.Draw(
            resources.GetTexture(texture_name.str()),
            util::Vector2<size_t>{1, kTopTextHeight + 1}
        );
      }
    } else if (cell == kArmorParameterIndex) {
      if (armor_) {
        cell_region.Draw(
            resources.GetTexture("drone_armor"),
            util::Vector2<size_t>{1, kTopTextHeight + 1}
        );
      }
    }
  }
}

}
