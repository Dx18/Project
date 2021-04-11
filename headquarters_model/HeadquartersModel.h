#pragma once

#include "config/ConfigStructure.h"
#include "config/GameConfig.h"

#include "Resources.h"
#include "tech/Tech.h"
#include "armory/Armory.h"

namespace headquarters_model {

/** Model of headquarters. */
class HeadquartersModel {
 public:
  /**
   * Creates headquarters model from config.
   * @param game_config Game config.
   * @param info Info about headquarters model.
   */
  HeadquartersModel(const config::GameConfig &game_config, const config::ConfigStructure &info);

  /** Returns reference to headquarters tech state. */
  tech::Tech &GetTech();
  /** Returns reference to headquarters armory. */
  armory::Armory &GetArmory();
  /** Returns const reference to headquarters resources. */
  const Resources &GetResources();

 private:
  /** Headquarters resources. */
  Resources resources_;
  /** Headquarters tech state. */
  tech::Tech tech_;
  /** Headquarters armory. */
  armory::Armory armory_;

};

}
