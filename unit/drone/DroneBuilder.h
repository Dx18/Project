#pragma once

#include "unit/UnitBuilder.h"

#include "Drone.h"

namespace unit::drone {

/** Drone builder. */
class DroneBuilder : UnitBuilder<DroneBuilder> {
 public:
  /** Sets drone weapon and returns current builder. */
  DroneBuilder &WithWeapon(std::unique_ptr<IDroneWeapon> weapon);
  /** Returns created drone. Internally current drone is reset to initial state. */
  [[nodiscard]] Drone Build();

 protected:
  Unit &CurrentUnit() override;

 private:
  /** Current drone. */
  Drone current_;

};

}


