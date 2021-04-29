#pragma once

#include "IArmor.h"

namespace unit {

/** Basic armor with fixed defence and mass. */
class BasicArmor : public virtual IArmor {
 public:
  /**
   * Creates basic armor instance.
   * @param defence Defence of armor.
   * @param mass Mass of armor.
   */
  BasicArmor(int defence, int mass);

  [[nodiscard]] int Defence() const override;
  [[nodiscard]] int Mass() const override;

 private:
  /** Defence of armor. */
  int defence_;
  /** Mass of armor. */
  int mass_;

};

}
