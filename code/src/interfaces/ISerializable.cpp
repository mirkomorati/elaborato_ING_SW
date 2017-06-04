/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#include "../../hdr/interfaces/ISerializable.hpp"

/**
 * ISerializable implementation
 */
bool mm::Serialized::isType(mm::StoredTypes type) const {
  return type == this->type;
}

const mm::SerializedUnion &mm::Serialized::get() const {
  return data;
}

mm::StoredTypes mm::Serialized::getType() const {
  return type;
}

mm::Serialized::Serialized(mm::StoredTypes t, mm::SerializedUnion data)
    : type(t), data(data) {}

mm::Serialized::~Serialized() {
  if (type == StoredTypes::TEXT){
    // su overflow è (&data.text)->string::~string()
    data.text.string::~string();
  }
}


