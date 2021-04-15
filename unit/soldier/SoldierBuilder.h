#pragma once

#include "unit/UnitBuilder.h"

#include "Soldier.h"

namespace unit::soldier {

/** Soldier builder. */
class SoldierBuilder : public UnitBuilder<SoldierBuilder> {
 public:
  /** Sets soldier primary weapon and returns current builder. */
  SoldierBuilder &WithPrimaryWeapon(std::unique_ptr<ISoldierWeapon> weapon);
  /** Sets soldier secondary weapon and returns current builder. */
  SoldierBuilder &WithSecondaryWeapon(std::unique_ptr<ISoldierWeapon> weapon);
  /** Sets soldier armor and returns current builder. */
  SoldierBuilder &WithArmor(std::unique_ptr<ISoldierArmor> armor);

  /** Returns current primary weapon of soldier. */
  [[nodiscard]] const ISoldierWeapon *PrimaryWeapon() const;
  /** Returns current secondary weapon of soldier. */
  [[nodiscard]] const ISoldierWeapon *SecondaryWeapon() const;
  /** Returns current armor of soldier. */
  [[nodiscard]] const ISoldierArmor *Armor() const;

  /** Returns created soldier. Internally current soldier is reset to initial state. */
  [[nodiscard]] Soldier Build();

 protected:
  Unit &CurrentUnit() override;
  [[nodiscard]] const Unit &CurrentUnit() const override;

 private:
  /** Current soldier. */
  Soldier current_;

};

}
