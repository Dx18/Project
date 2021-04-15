#include "DroneStandardArmorFactory.h"

namespace unit::drone::armor::standard {

DroneStandardArmorFactory::DroneStandardArmorFactory(const Tech &tech)
    : tech_(tech) {

}

std::unique_ptr<IDroneArmor> DroneStandardArmorFactory::CreateArmor() const {
  return std::make_unique<DroneStandardArmor>(tech_);
}

}
