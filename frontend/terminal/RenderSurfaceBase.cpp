#include "RenderSurfaceBase.h"

namespace frontend::terminal {

RenderSurfaceBase::RenderSurfaceBase()
    : data_(), size_({0, 0}) {

}

RenderSurfaceBase::RenderSurfaceBase(const util::Vector2<size_t> &size, const CharData &char_data)
    : data_(size.x * size.y, char_data), size_(size) {

}

util::Vector2<size_t> RenderSurfaceBase::Size() const {
  return size_;
}

void RenderSurfaceBase::ResizeClear(const util::Vector2<size_t> &new_size, const CharData &char_data) {
  data_.clear();
  data_.assign(new_size.x * new_size.y, char_data);
  size_ = new_size;
}

const CharData &RenderSurfaceBase::Get(const util::Vector2<size_t> &position) const {
  CheckIfContainsPoint(position);
  return data_[GetCharIndex(position)];
}

CharData &RenderSurfaceBase::Get(const util::Vector2<size_t> &position) {
  CheckIfContainsPoint(position);
  return data_[GetCharIndex(position)];
}

size_t RenderSurfaceBase::GetCharIndex(const util::Vector2<size_t> &position) const {
  return position.y * size_.x + position.x;
}

}
