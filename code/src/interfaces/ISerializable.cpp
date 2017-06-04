/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#include <iostream>
#include "../../hdr/interfaces/ISerializable.hpp"

/**
 * ISerializable implementation
 */
bool mm::Serialized::isType(mm::StoredTypes type) const noexcept {
  return type == this->type;
}

const mm::SerializedUnion &mm::Serialized::get() const noexcept {
  return data;
}

mm::StoredTypes mm::Serialized::getType() const noexcept {
  return type;
}

mm::Serialized::Serialized(mm::StoredTypes t, mm::SerializedUnion data) noexcept
    : type(t) {
  switch (t){
    case INTEGER:
      this->data.integer = data.integer;
      break;
    case REAL:
      this->data.real = data.real;
      break;
    case TEXT:
      this->data.text = data.text;
      break;
  }
}

std::ostream &mm::operator<<(std::ostream &os, const mm::Serialized &data){
  switch (data.type){
    case mm::INTEGER:
      return (os << data.data.integer);
    case mm::REAL:
      return (os << data.data.real);
    case mm::TEXT:
      return (os << data.data.text);
  }
  return os;
}

mm::Serialized::~Serialized() noexcept {
  if(type == mm::TEXT){
    data.text.~basic_string<char>();
  }
}

mm::Serialized::Serialized() noexcept {
  type = mm::INTEGER;
  data.integer = 0;
}

mm::SerializedUnion::SerializedUnion() noexcept : text() {
}
