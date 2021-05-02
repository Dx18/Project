#pragma once

#include "IWeapon.h"

namespace unit {

/** Basic laser weapon. Has infinite number of shots and cannot be reloaded. */
class BasicLaserWeapon : public virtual IWeapon {
 public:
  /**
   * Creates basic laser weapon instance.
   * @param mass Mass of weapon.
   * @param base_damage Base damage of weapon.
   */
  explicit BasicLaserWeapon(int mass, int base_damage);

  [[nodiscard]] std::optional<int> ShotsLeft() const override;
  [[nodiscard]] std::optional<int> MaxShots() const override;
  [[nodiscard]] int Mass() const override;
  [[nodiscard]] bool CanBeReloaded() const override;
  void Reload() override;
  int BaseDamage() const override;

 private:
  /** Mass of weapon. */
  int mass_;
  /** Base damage of weapon. */
  int base_damage_;

};

}
