#pragma once

#include <string>
#include <memory>

#include "config/GameConfig.h"
#include "util/Vector.h"
#include "util/Math.h"
#include "world/map/WorldMap.h"
#include "world/map/WorldMovementMap.h"

namespace world::script {

class IWorldScript;

}

namespace unit {

/** Unit. */
class Unit {
 public:
  virtual ~Unit() = 0;

  /** Returns name of unit. */
  [[nodiscard]] const std::string &Name() const;
  /**
   * Sets name of unit.
   * @param name Name to set.
   */
  void SetName(const std::string &name);

  /** Returns health of unit. */
  [[nodiscard]] int Health() const;
  /**
   * Sets health of unit.
   * @param health Health to set.
   */
  void SetHealth(int health);

  /** Returns base health of unit. */
  [[nodiscard]] int BaseHealth() const;
  /**
   * Sets base health of unit.
   * @param base_health Base health to set.
   */
  void SetBaseHealth(int base_health);

  /** Returns max health of unit. */
  [[nodiscard]] virtual int MaxHealth() const = 0;

  /**
   * Max distance unit can travel.
   * @param game_config Const reference to game config.
   */
  [[nodiscard]] virtual int MaxTravelDistance(const config::GameConfig &game_config) const = 0;

  /** Returns position of unit. */
  [[nodiscard]] util::Vector3<double> Position() const;
  /**
   * Sets position of unit.
   * @param position Position to set.
   */
  void SetPosition(util::Vector3<double> position);

  /**
   * Creates unit moving script.
   * @param unit_id ID of current unit.
   * @param map World map.
   * @param game_config Const reference to game config.
   * @param position Target position.
   */
  std::unique_ptr<world::script::IWorldScript>
  CreateMovementScript(size_t unit_id, const world::map::WorldMap &map, const config::GameConfig &game_config,
                       util::Vector3<double> position);

 private:
  /** Name of unit. */
  std::string name_;
  /** Health of unit. */
  int health_;
  /** Max health of unit. */
  int max_health_;
  /** Current position of unit. */
  util::Vector3<double> position_;

};

}
