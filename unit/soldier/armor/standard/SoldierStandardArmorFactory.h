#pragma once

#include "headquarters_model/tech/Tech.h"

#include "../ISoldierArmorFactory.h"
#include "SoldierStandardArmor.h"

namespace unit::soldier::armor::standard {

/** Factory which creates soldier standard armor. */
class SoldierStandardArmorFactory : public ISoldierArmorFactory {
 private:
  /** Const reference to headquarters tech. */
  const Tech &tech_;

 public:
  /**
   * Creates soldier standard armor factory.
   * @param tech Current tech state.
   */
  explicit SoldierStandardArmorFactory(const Tech &tech);

  [[nodiscard]] std::unique_ptr<ISoldierArmor> CreateArmor() const override;

};

}
