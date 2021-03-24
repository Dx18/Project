#include "IArmor.h"

namespace unit {

BasicArmor::BasicArmor(int defence, int mass)
    : defence_(defence), mass_(mass) {

}

int BasicArmor::Defence() const {
  return defence_;
}

int BasicArmor::Mass() const {
  return mass_;
}

}
