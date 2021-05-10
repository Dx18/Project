#include "FloorMaterial.h"

namespace world::map {

FloorMaterial::FloorMaterial(FloorMaterialType _type, std::string _name)
    : type(_type), name(std::move(_name)) {

}

const FloorMaterial FloorMaterial::kWood
    (FloorMaterialType::kWood,
     "wood");
const FloorMaterial FloorMaterial::kGrass
    (FloorMaterialType::kGrass,
     "grass");
const FloorMaterial FloorMaterial::kAsphalt
    (FloorMaterialType::kAsphalt,
     "asphalt");

const std::array<FloorMaterial, 3> kFloorMaterial = {
    FloorMaterial::kWood,
    FloorMaterial::kGrass,
    FloorMaterial::kAsphalt
};

}
