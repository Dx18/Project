#pragma once

#include "headquarters_model/tech/Tech.h"

#include "../IDroneArmorFactory.h"
#include "DroneCompositeArmor.h"

namespace unit::drone::armor::composite {

/** Factory which creates drone composite armor. */
class DroneCompositeArmorFactory : public IDroneArmorFactory {
 private:
  /** Const reference to headquarters tech. */
  const Tech &tech_;

 public:
  /**
   * Creates drone composite armor factory.
   * @param tech Current tech state.
   */
  explicit DroneCompositeArmorFactory(const Tech &tech);

  [[nodiscard]] std::unique_ptr<IDroneArmor> CreateArmor() const override;

};

}
