#include "TerminalResources.h"

namespace frontend::terminal {

TerminalResources::TerminalResources(std::string base_path)
    : base_path_(std::move(base_path)), textures_(), texture_reader_() {

}

const RenderSurfaceBase &TerminalResources::GetTexture(const std::string &name) {
  auto iter = textures_.find(name);
  if (iter != textures_.end()) {
    return iter->second;
  }

  std::stringstream path;
  path << base_path_ << "/textures/" << name << ".texture";

  std::ifstream input(path.str());
  RenderSurfaceBase texture = texture_reader_.ReadTexture(input);
  input.close();

  textures_.insert({name, texture});
  return textures_.find(name)->second;
}

}
