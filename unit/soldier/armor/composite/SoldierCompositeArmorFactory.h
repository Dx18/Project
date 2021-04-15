#pragma once

#include "headquarters_model/tech/Tech.h"

#include "../ISoldierArmorFactory.h"
#include "SoldierCompositeArmor.h"

namespace unit::soldier::armor::composite {

/** Factory which creates soldier composite armor. */
class SoldierCompositeArmorFactory : public ISoldierArmorFactory {
 private:
  /** Const reference to headquarters tech. */
  const Tech &tech_;

 public:
  /**
   * Creates soldier composite armor factory.
   * @param tech Current tech state.
   */
  explicit SoldierCompositeArmorFactory(const Tech &tech);

  [[nodiscard]] std::unique_ptr<ISoldierArmor> CreateArmor() const override;

};

}
