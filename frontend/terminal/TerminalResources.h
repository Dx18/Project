#pragma once

#include <unordered_map>
#include <fstream>

#include "RenderSurfaceBase.h"
#include "TextureReader.h"

namespace frontend::terminal {

/** Terminal resources. */
class TerminalResources {
 public:
  /**
   * Creates terminal resources.
   * @param base_path Path to directory with resources.
   */
  explicit TerminalResources(std::string base_path);

  /**
   * Returns texture by name. If texture was not loaded yet, then it's loaded. Method throws `std::runtime_error` if
   * texture reading is failed.
   * @param name Name of texture.
   */
  const RenderSurfaceBase &GetTexture(const std::string &name);

 private:
  /** Path to directory with resources. */
  std::string base_path_;
  /** Loaded textures. */
  std::unordered_map<std::string, RenderSurfaceBase> textures_;
  /** Texture reader. */
  TextureReader texture_reader_;

};

}
