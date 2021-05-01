#pragma once

#include <memory>

#include "unit/Unit.h"

#include "weapon/ISoldierWeapon.h"
#include "armor/ISoldierArmor.h"

namespace unit::soldier {

using namespace unit::soldier::weapon;
using namespace unit::soldier::armor;

/** Soldier unit. */
class Soldier : public Unit {
 public:
  Soldier();
  Soldier(const Soldier &other) = delete;
  Soldier(Soldier &&other) noexcept;

  [[nodiscard]] int MaxHealth() const override;
  [[nodiscard]] int MaxTravelDistance(const config::GameConfig &game_config) const override;

  /** Returns true if soldier has primary weapon. */
  [[nodiscard]] bool HasPrimaryWeapon() const;
  /** Returns const pointer to soldier's primary weapon. If there is no weapon then `nullptr` is returned. */
  [[nodiscard]] const ISoldierWeapon *PrimaryWeapon() const;
  /**
   * Sets soldier primary weapon.
   * @param weapon Weapon to set.
   */
  void SetPrimaryWeapon(std::unique_ptr<ISoldierWeapon> weapon);

  /** Returns true if soldier has secondary weapon. */
  [[nodiscard]] bool HasSecondaryWeapon() const;
  /** Returns const pointer to soldier's secondary weapon. If there is no weapon then `nullptr` is returned. */
  [[nodiscard]] const ISoldierWeapon *SecondaryWeapon() const;
  /**
   * Sets soldier secondary weapon.
   * @param weapon Weapon to set.
   */
  void SetSecondaryWeapon(std::unique_ptr<ISoldierWeapon> weapon);

  /** Returns true if currently selected weapon is primary. */
  [[nodiscard]] bool IsPrimaryWeaponSelected() const;
  /**
   * Selects weapon.
   * @param primary True if primary weapon must be selected.
   */
  void SelectWeapon(bool primary);
  /** Toggles selected weapon. */
  void ToggleWeapon();

  /** Returns true if soldier has armor. */
  [[nodiscard]] bool HasArmor() const;
  /** Returns const pointer to soldier's armor. If there is no armor then `nullptr` is returned. */
  [[nodiscard]] const ISoldierArmor *Armor() const;
  /**
   * Sets soldier armor.
   * @param armor Armor to set.
   */
  void SetArmor(std::unique_ptr<ISoldierArmor> armor);

  Soldier &operator=(const Soldier &other) = delete;
  Soldier &operator=(Soldier &&other) noexcept;

 private:
  /** Primary weapon. */
  std::unique_ptr<ISoldierWeapon> primary_weapon_;
  /** Secondary weapon. */
  std::unique_ptr<ISoldierWeapon> secondary_weapon_;
  /** True if currently selected weapon is primary. */
  bool is_primary_weapon_selected_;
  /** Armor. */
  std::unique_ptr<ISoldierArmor> armor_;

};

}
