#pragma once

#include "IWeapon.h"

namespace unit {

/** Basic laser weapon. Has infinite number of shots and cannot be reloaded. */
class BasicLaserWeapon : public virtual IWeapon {
 public:
  /**
   * Creates basic laser weapon instance.
   * @param mass Mass of weapon.
   */
  explicit BasicLaserWeapon(int mass);

  [[nodiscard]] std::optional<int> ShotsLeft() const override;
  [[nodiscard]] std::optional<int> MaxShots() const override;
  [[nodiscard]] int Mass() const override;
  [[nodiscard]] bool CanBeReloaded() const override;
  void Reload() override;

 private:
  /** Mass of weapon. */
  int mass_;

};

}
