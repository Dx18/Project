#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "unit/Unit.h"

#include "Projectile.h"

namespace world::entities {

/** Entities in game world. */
class WorldEntities {
 public:
  /**
   * Creates world entities.
   * @param player_units Player's units.
   * @param enemy_units Enemy's units.
   */
  WorldEntities(std::vector<std::unique_ptr<unit::Unit>> &&player_units,
                std::vector<std::unique_ptr<unit::Unit>> &&enemy_units);

  /**
   * Updates world entities.
   * @param delta Time passed since last frame.
   */
  void Update(std::chrono::microseconds delta);

  /**
   * Returns ID of player unit with given index.
   * @param index Index of unit.
   */
  [[nodiscard]] size_t PlayerUnitID(size_t index) const;
  /**
   * Returns ID of enemy unit with given index.
   * @param index Index of unit.
   */
  [[nodiscard]] size_t EnemyUnitID(size_t index) const;

  /**
   * Returns reference to unit with given ID. Throws `std::runtime_error` if unit with given ID does not exist.
   * @param unit_id ID of unit.
   */
  unit::Unit &GetUnit(size_t unit_id);
  /**
   * Returns const reference to unit with given ID. Throws `std::runtime_error` if unit with given ID does not exist.
   * @param unit_id ID of unit.
   */
  [[nodiscard]] const unit::Unit &GetUnit(size_t unit_id) const;

  /** Returns const reference to array of player's units. */
  [[nodiscard]] const std::vector<std::unique_ptr<unit::Unit>> &PlayerUnits() const;
  /** Returns const reference to array of enemy's units. */
  [[nodiscard]] const std::vector<std::unique_ptr<unit::Unit>> &EnemyUnits() const;

  /**
   * Adds projectile to game world and returns its ID.
   * @param projectile ID of projectile.
   */
  size_t CreateProjectile(const Projectile &projectile);
  /**
   * Returns true if projectile was not removed from game world and is still alive.
   * @param projectile_id ID of projectile.
   */
  [[nodiscard]] bool IsProjectileAlive(size_t projectile_id) const;

  /** Returns const reference to array of projectiles. */
  [[nodiscard]] const std::vector<Projectile> &Projectiles() const;

 private:
  /** Player's units. */
  std::vector<std::unique_ptr<unit::Unit>> player_units_;
  /** Enemy's units. */
  std::vector<std::unique_ptr<unit::Unit>> enemy_units_;
  /** Map from player's unit ID to its index in array of player's units. */
  std::unordered_map<size_t, size_t> player_unit_id_to_index_;
  /** Map from player's unit index in array of player's units to its ID. */
  std::unordered_map<size_t, size_t> player_index_to_unit_id_;
  /** Map from enemy's unit ID to its index in array of enemy's units. */
  std::unordered_map<size_t, size_t> enemy_unit_id_to_index_;
  /** Map from enemy's unit index in array of enemy's units to its ID. */
  std::unordered_map<size_t, size_t> enemy_index_to_unit_id_;
  /** Projectiles in game world. */
  std::vector<Projectile> projectiles_;
  /** Counter of projectile IDs. */
  size_t projectile_id_counter_;
  /** Map from projectile's ID to its index in array of projectiles. */
  std::unordered_map<size_t, size_t> projectile_id_to_index_;
  /** Map from projectile's index in array of projectiles to its ID. */
  std::unordered_map<size_t, size_t> projectile_index_to_id_;

  /**
   * Removes projectile with given index. Does not check index for correctness.
   * @param index Index of projectile to remove.
   */
  void RemoveProjectile(size_t index);

};

}
