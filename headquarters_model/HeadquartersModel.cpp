#include "HeadquartersModel.h"

namespace headquarters_model {

HeadquartersModel::HeadquartersModel(const config::GameConfig &game_config)
    : resources_(), tech_(game_config, resources_), armory_(resources_) {

}

HeadquartersModel::HeadquartersModel(const config::GameConfig &game_config, const config::ConfigStructure &info)
    : resources_(info.sections.at("Resources")),
      tech_(game_config, info.sections.at("Tech"), resources_),
      armory_(info.sections.at("Armory"), resources_) {

}

tech::Tech &HeadquartersModel::GetTech() {
  return tech_;
}

const tech::Tech &HeadquartersModel::GetTech() const {
  return tech_;
}

armory::Armory &HeadquartersModel::GetArmory() {
  return armory_;
}

const armory::Armory &HeadquartersModel::GetArmory() const {
  return armory_;
}

const Resources &HeadquartersModel::GetResources() {
  return resources_;
}

}
