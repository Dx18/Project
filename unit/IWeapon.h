#pragma once

#include <optional>

namespace unit {

/** Common interface for unit weapon. */
class IWeapon {
 public:
  /** Virtual destructor. */
  virtual ~IWeapon() = 0;

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
  /** Returns base damage of weapon. */
  [[nodiscard]] virtual int BaseDamage() const = 0;

};

}
