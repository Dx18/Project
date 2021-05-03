#pragma once

#include <memory>

#include "ISoldierArmor.h"

namespace unit::soldier::armor {

/** Abstract factory which creates soldier armor. */
class ISoldierArmorFactory {
 public:
  /** Creates soldier armor. */
  [[nodiscard]] virtual std::unique_ptr<ISoldierArmor> CreateArmor() const = 0;

};

}
