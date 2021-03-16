#pragma once

#include <optional>

namespace unit {

/** Common interface for unit weapon. */
class IWeapon {
 public:
  /** Number of shots left. If returned value does not have a value then result can be considered as infinity. */
  [[nodiscard]] virtual std::optional<int> ShotsLeft() const = 0;
  /** Max number of shots left. If returned value does not have a value then result can be considered as infinity. */
  [[nodiscard]] virtual std::optional<int> MaxShots() const = 0;
  /** Mass of weapon. */
  [[nodiscard]] virtual int Mass() const = 0;
  /** Returns true if current weapon can be reloaded. */
  [[nodiscard]] virtual bool CanBeReloaded() const = 0;
  /** Reloads weapon. */
  virtual void Reload() = 0;

};

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