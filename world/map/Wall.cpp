#include "Wall.h"

namespace world::map {

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

size_t hash<world::map::Wall>::operator()(const world::map::Wall &wall) const {
  return hash<world::map::WallForm>{}(wall.form);
}

}
