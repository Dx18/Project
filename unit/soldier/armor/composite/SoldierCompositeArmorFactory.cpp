#include "SoldierCompositeArmorFactory.h"

namespace unit::soldier::armor::composite {

SoldierCompositeArmorFactory::SoldierCompositeArmorFactory(const Tech &tech)
    : tech_(tech) {

}

std::unique_ptr<ISoldierArmor> SoldierCompositeArmorFactory::CreateArmor() const {
  return std::make_unique<SoldierCompositeArmor>(tech_);
}

}
