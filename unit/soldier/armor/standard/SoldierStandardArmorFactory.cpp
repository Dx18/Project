#include "SoldierStandardArmorFactory.h"

namespace unit::soldier::armor::standard {

SoldierStandardArmorFactory::SoldierStandardArmorFactory(const Tech &tech)
    : tech_(tech) {

}

std::unique_ptr<ISoldierArmor> SoldierStandardArmorFactory::CreateArmor() const {
  return std::make_unique<SoldierStandardArmor>(tech_);
}

}
