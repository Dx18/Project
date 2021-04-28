#include "Wall.h"

namespace world {

Wall::Wall(WallForm _form)
    : form(_form) {

}

bool Wall::operator==(const Wall &other) const {
  return form == other.form;
}

bool Wall::operator!=(const Wall &other) const {
  return !(*this == other);
}

}

namespace std {

size_t hash<world::Wall>::operator()(const world::Wall &wall) const {
  return hash<world::WallForm>{}(wall.form);
}

}
