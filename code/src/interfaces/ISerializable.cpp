/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#include <iostream>
#include <sstream>
#include "../../hdr/interfaces/ISerializable.hpp"

bool mm::Serialized::isType(mm::StoredTypes type) const noexcept {
  return type == this->type;
}

mm::StoredTypes mm::Serialized::getType() const noexcept {
  return type;
}

std::ostream &mm::operator<<(std::ostream &os, const mm::Serialized &data){
  switch (data.type){
    case mm::INTEGER:
      return (os << data.data.integer);
    case mm::REAL:
      return (os << data.data.real);
    case mm::TEXT:
      return (os << "'" <<data.data.text << "'");
  }
  return os;
}

mm::Serialized::Serialized() noexcept {
  type = mm::INTEGER;
  data.integer = 0;
}

mm::Serialized::Serialized(mm::StoredTypes t, std::string data) noexcept
  : type(t){
  this->data.text = new char[data.length()];
  strcpy(this->data.text, data.c_str());
}

mm::Serialized::Serialized(mm::StoredTypes t, int data) noexcept :type(t) {
  this->data.integer = data;
}

mm::Serialized::Serialized(mm::StoredTypes t, double data) noexcept : type(t){
  this->data.real = data;
}

mm::Serialized::~Serialized() noexcept {
  if (type == mm::TEXT and data.text != nullptr){
    delete[] data.text;
  }
}

mm::Serialized::Serialized(const mm::Serialized &old) noexcept : type(old.type){
  if (type == mm::TEXT){
    this->data.text = new char[strlen(old.data.text)];
    strcpy(this->data.text, old.data.text);
  } else if (type == mm::INTEGER){
    this->data.integer = old.data.integer;
  } else {
    this->data.real = old.data.real;
  }
}

const mm::Serialized &mm::Serialized::operator=(const mm::Serialized &old) {
  switch (old.type){
    case INTEGER:
      this->type = old.type;
      this->data.integer = old.data.integer;
      break;
    case REAL:
      this->type = old.type;
      this->data.real = old.data.real;
      break;
    case TEXT:
      this->type = old.type;
      this->data.text = new char[strlen(old.data.text)];
      strcpy(this->data.text, old.data.text);
      break;
  }
  return *this;
}

const std::string &mm::Serialized::get_str() const noexcept(false) {
  if (type != mm::TEXT){
    throw std::runtime_error("The type of the object is not TEXT!");
  }

  return std::string(data.text);
}

int mm::Serialized::get_int() const noexcept(false) {
  if (type != mm::INTEGER){
    throw std::runtime_error("The type of the object is not INTEGER!");
  }

  return data.integer;
}

double mm::Serialized::get_real() const noexcept(false) {
  if (type != mm::REAL){
    throw std::runtime_error("The type of the object is not REAL!");
  }

  return data.real;
}