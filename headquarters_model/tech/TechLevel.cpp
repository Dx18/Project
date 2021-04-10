#include "Tech.h"

namespace headquarters_model::tech {

TechLevel tech_level_from_int(int value) {
  if (value == TechLevel::kNotResearched) {
    return TechLevel::kNotResearched;
  } else if (value == TechLevel::kBasic) {
    return TechLevel::kBasic;
  } else if (value == TechLevel::kAdvanced) {
    return TechLevel::kAdvanced;
  }

  std::stringstream message;
  message << "given value (" << value << ") cannot be converted to TechLevel";
  throw std::runtime_error(message.str());
}

}
