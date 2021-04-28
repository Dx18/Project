#include "TextureReader.h"

namespace frontend::terminal {

RenderSurfaceBase TextureReader::ReadTexture(std::istream &in) const {
  size_t height, width;
  if (!(in >> height)) {
    throw std::runtime_error("failed to read texture height");
  }
  if (!(in >> width)) {
    throw std::runtime_error("failed to read texture width");
  }

  std::string line;
  // Ensuring that next line character is skipped
  std::getline(in, line);

  std::string chars;
  for (size_t row = 0; row < height; ++row) {
    if (!std::getline(in, line)) {
      throw std::runtime_error("failed to read texture: unexpected EOF");
    }

    if (!(line.size() == width || (line.size() == width + 1 && line.back() == ';'))) {
      throw std::runtime_error("failed to read texture: length of line must be equal to width");
    }

    chars.append(line.begin(), line.begin() + width);
  }

  std::array<std::vector<Color>, 2> colors;
  for (size_t index = 0; index < 2; ++index) {
    for (size_t row = 0; row < height; ++row) {
      if (!std::getline(in, line)) {
        throw std::runtime_error("failed to read texture: unexpected EOF");
      }

      if (line.size() != width) {
        throw std::runtime_error("failed to read texture: length of line must be equal to width");
      }

      for (size_t column = 0; column < width; ++column) {
        if (line[column] < '0' || line[column] >= '0' + kColors.size()) {
          throw std::runtime_error("failed to read texture: invalid color value");
        }

        colors[index].push_back(kColors[line[column] - '0']);
      }
    }
  }

  RenderSurfaceBase result(
      {width, height},
      CharData(' ', ColorPair(Color::kWhite, Color::kBlack))
  );

  for (size_t row = 0; row < height; ++row) {
    for (size_t column = 0; column < width; ++column) {
      size_t index = row * width + column;

      result.Get({column, row}) = CharData(
          chars[index],
          ColorPair(colors[0][index], colors[1][index])
      );
    }
  }

  return result;
}

}
