#include "Resources.h"

namespace headquarters_model {

Resources::Resources(const config::ConfigSectionStructure &resources_info)
    : matter(std::stoi(resources_info.values.at("matter"))) {

}

}