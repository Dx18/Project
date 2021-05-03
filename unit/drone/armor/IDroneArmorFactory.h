#pragma once

#include <memory>

#include "IDroneArmor.h"

namespace unit::drone::armor {

/** Abstract factory which creates drone armor. */
class IDroneArmorFactory {
 public:
  /** Creates drone armor. */
  [[nodiscard]] virtual std::unique_ptr<IDroneArmor> CreateArmor() const = 0;

};

}
