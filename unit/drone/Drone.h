#pragma once

#include <memory>

#include "unit/Unit.h"

#include "weapon/IDroneWeapon.h"
#include "armor/IDroneArmor.h"

namespace unit::drone {

using namespace unit::drone::weapon;
using namespace unit::drone::armor;

/** Drone unit. */
class Drone : public Unit {
 public:
  Drone() = default;
  Drone(const Drone &other) = delete;
  Drone(Drone &&other) noexcept;

  [[nodiscard]] int MaxHealth() const override;
  [[nodiscard]] int MaxTravelDistance(const config::GameConfig &game_config) const override;
  [[nodiscard]] bool HasActiveWeapon() const override;
  [[nodiscard]] const IWeapon &ActiveWeapon() const override;
  [[nodiscard]] bool HasActiveArmor() const override;
  [[nodiscard]] const IArmor &ActiveArmor() const override;

  /** Returns true if drone has weapon. */
  [[nodiscard]] bool HasWeapon() const;
  /** Returns const pointer to drone's weapon. If there is no weapon then `nullptr` is returned. */
  [[nodiscard]] const IDroneWeapon *Weapon() const;
  /**
   * Sets drone weapon.
   * @param weapon Weapon to set.
   */
  void SetWeapon(std::unique_ptr<IDroneWeapon> weapon);

  /** Returns true if drone has armor. */
  [[nodiscard]] bool HasArmor() const;
  /** Returns const pointer to drone's armor. If there is no armor then `nullptr` is returned. */
  [[nodiscard]] const IDroneArmor *Armor() const;
  /**
   * Sets drone armor.
   * @param armor Armor to set.
   */
  void SetArmor(std::unique_ptr<IDroneArmor> armor);

  Drone &operator=(const Drone &other) = delete;
  Drone &operator=(Drone &&other) noexcept;

 private:
  /** Weapon. */
  std::unique_ptr<IDroneWeapon> weapon_;
  /** Armor. */
  std::unique_ptr<IDroneArmor> armor_;

};

}
