#pragma once

#include "IWeapon.h"

namespace unit {

/** Basic firearm weapon with ammo counter. Can be reloaded. */
class BasicFirearmWeapon : public virtual IWeapon {
 public:
  /**
   * Creates basic firearm weapon instance.
   * @param ammo Initial ammo.
   * @param max_ammo Max possible ammo.
   * @param mass Mass of weapon.
   */
  BasicFirearmWeapon(int ammo, int max_ammo, int mass);

  [[nodiscard]] std::optional<int> ShotsLeft() const override;
  [[nodiscard]] std::optional<int> MaxShots() const override;
  [[nodiscard]] int Mass() const override;
  [[nodiscard]] bool CanBeReloaded() const override;
  void Reload() override;

 private:
  /** Current ammo. */
  int ammo_;
  /** Max possible ammo. */
  int max_ammo_;
  /** Mass of weapon. */
  int mass_;

};

}
