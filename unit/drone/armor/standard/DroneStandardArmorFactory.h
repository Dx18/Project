#pragma once

#include "headquarters_model/tech/Tech.h"

#include "../IDroneArmorFactory.h"
#include "DroneStandardArmor.h"

namespace unit::drone::armor::standard {

/** Factory which creates drone standard armor. */
class DroneStandardArmorFactory : public IDroneArmorFactory {
 private:
  /** Const reference to headquarters tech. */
  const Tech &tech_;

 public:
  /**
   * Creates drone standard armor factory.
   * @param tech Current tech state.
   */
  explicit DroneStandardArmorFactory(const Tech &tech);

  [[nodiscard]] std::unique_ptr<IDroneArmor> CreateArmor() const override;

};

}
