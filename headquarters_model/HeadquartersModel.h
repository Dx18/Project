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
   * Creates empty headquarters model.
   * @param game_config Game config.
   */
  explicit HeadquartersModel(const config::GameConfig &game_config);

  /**
   * Creates headquarters model from config.
   * @param game_config Game config.
   * @param info Info about headquarters model.
   */
  HeadquartersModel(const config::GameConfig &game_config, const config::ConfigStructure &info);

  /** Returns reference to headquarters tech state. */
  tech::Tech &GetTech();
  /** Returns const reference to headquarters tech state. */
  [[nodiscard]] const tech::Tech &GetTech() const;
  /** Returns reference to headquarters armory. */
  armory::Armory &GetArmory();
  /** Returns const reference to headquarters armory. */
  [[nodiscard]] const armory::Armory &GetArmory() const;
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
