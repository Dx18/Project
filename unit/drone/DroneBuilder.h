#pragma once

#include "unit/UnitBuilder.h"

#include "Drone.h"

namespace unit::drone {

/** Drone builder. */
class DroneBuilder : public UnitBuilder<DroneBuilder> {
 public:
  /** Sets drone weapon and returns current builder. */
  DroneBuilder &WithWeapon(std::unique_ptr<IDroneWeapon> weapon);
  /** Sets drone armor and returns current builder. */
  DroneBuilder &WithArmor(std::unique_ptr<IDroneArmor> armor);
  /** Returns created drone. Internally current drone is reset to initial state. */

  /** Returns current weapon of drone. */
  [[nodiscard]] const IDroneWeapon *Weapon() const;
  /** Returns current armor of drone. */
  [[nodiscard]] const IDroneArmor *Armor() const;

  [[nodiscard]] Drone Build();

 protected:
  Unit &CurrentUnit() override;
  [[nodiscard]] const Unit &CurrentUnit() const override;

 private:
  /** Current drone. */
  Drone current_;

};

}
