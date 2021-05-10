#pragma once

#include <string>
#include <memory>

#include "IWeapon.h"
#include "IArmor.h"

#include "config/GameConfig.h"
#include "util/Vector.h"
#include "util/Math.h"
#include "world/map/WorldMap.h"
#include "world/map/WorldMovementMap.h"
#include "world/map/WorldVisibilityMap.h"

namespace world::script {

class IWorldScript;

}

namespace world {

class World;

}

namespace unit {

/** Unit. */
class Unit {
 public:
  virtual ~Unit() = 0;

  Unit();

  /** Move constructor. */
  Unit(Unit &&other) noexcept;

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

  /** Returns true if unit has currently active weapon. */
  [[nodiscard]] virtual bool HasActiveWeapon() const = 0;
  /** Returns currently active weapon. */
  [[nodiscard]] virtual const IWeapon &ActiveWeapon() const = 0;

  /** Returns true if unit has currently active armor. */
  [[nodiscard]] virtual bool HasActiveArmor() const = 0;
  /** Returns currently active armor. */
  [[nodiscard]] virtual const IArmor &ActiveArmor() const = 0;

  /** Returns position of unit. */
  [[nodiscard]] util::Vector3<double> Position() const;
  /**
   * Sets position of unit.
   * @param position Position to set.
   */
  void SetPosition(util::Vector3<double> position);

  /**
   * Creates map of possible movement.
   * @param world Game world.
   * @param game_config Const reference to game config.
   */
  [[nodiscard]] world::map::WorldMovementMap CreateMovementMap(const world::World &world,
                                                               const config::GameConfig &game_config) const;

  /**
   * Creates map of visibility.
   * @param world Game world.
   * @param game_config Const reference to game config.
   */
  [[nodiscard]] world::map::WorldVisibilityMap
  CreateVisibilityMap(const world::World &world, const config::GameConfig &game_config) const;

  /**
   * Creates unit moving script.
   * @param unit_id ID of current unit.
   * @param world Game world.
   * @param game_config Const reference to game config.
   * @param position Target position.
   */
  std::unique_ptr<world::script::IWorldScript>
  CreateMovementScript(size_t unit_id, const world::World &world, const config::GameConfig &game_config,
                       util::Vector3<double> position);

  /**
   * Creates unit attack script.
   * @param world Game world.
   * @param game_config Const reference to game config.
   * @param target_unit_id ID of target unit.
   */
  std::unique_ptr<world::script::IWorldScript>
  CreateAttackScript(world::World &world, const config::GameConfig &game_config, size_t target_unit_id);

  Unit &operator=(Unit &&other) noexcept;

 private:
  /** Name of unit. */
  std::string name_;
  /** Health of unit. */
  int health_;
  /** Base health of unit. */
  int base_health_;
  /** Current position of unit. */
  util::Vector3<double> position_;

};

}
