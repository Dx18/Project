#include "DroneCompositeArmorFactory.h"

namespace unit::drone::armor::composite {

DroneCompositeArmorFactory::DroneCompositeArmorFactory(const Tech &tech)
    : tech_(tech) {

}

std::unique_ptr<IDroneArmor> DroneCompositeArmorFactory::CreateArmor() const {
  return std::make_unique<DroneCompositeArmor>(tech_);
}

}
