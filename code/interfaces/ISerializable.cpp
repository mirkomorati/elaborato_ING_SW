/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */

#include <iostream>
#include <sstream>
#include "ISerializable.hpp"

bool mm::Serialized::isType(mm::StoredTypes type) const noexcept {
    return type == this->type;
}

mm::StoredTypes mm::Serialized::get_type() const noexcept {
    return type;
}

std::ostream &mm::operator<<(std::ostream &os, const mm::Serialized &data) {
    switch (data.type) {
        case mm::INTEGER:
            return (os << data.data.integer);
        case mm::REAL:
            return (os << data.data.real);
        case mm::TEXT:
            return (os << "'" << data.data.text << "'");
    }
    return os;
}

mm::Serialized::Serialized() noexcept {
    type = mm::INTEGER;
    data.integer = 0;
}

mm::Serialized::Serialized(std::string data) noexcept
        : type(mm::TEXT) {
    this->data.text = new char[data.length() + 1];
    strcpy(this->data.text, data.c_str());
}

mm::Serialized::Serialized(int data) noexcept
        : type(mm::INTEGER) {
    this->data.integer = data;
}

mm::Serialized::Serialized(double data) noexcept
        : type(mm::REAL) {
    this->data.real = data;
}

mm::Serialized::~Serialized() noexcept {
    if (type == mm::TEXT and data.text != nullptr) {
        delete[] data.text;
    }
}

mm::Serialized::Serialized(const mm::Serialized &old) noexcept : type(old.type) {
    if (type == mm::TEXT) {
        this->data.text = new char[strlen(old.data.text) + 1];
        strcpy(this->data.text, old.data.text);
    } else if (type == mm::INTEGER) {
        this->data.integer = old.data.integer;
    } else {
        this->data.real = old.data.real;
    }
}

mm::Serialized &mm::Serialized::operator=(const mm::Serialized &old) {
    switch (old.type) {
        case mm::INTEGER:
            this->type = mm::INTEGER;
            this->data.integer = old.data.integer;
            break;
        case mm::REAL:
            this->type = mm::REAL;
            this->data.real = old.data.real;
            break;
        case mm::TEXT:
            this->type = mm::TEXT;
            this->data.text = new char[strlen(old.data.text) + 1];
            strcpy(this->data.text, old.data.text);
            break;
    }
    return *this;
}

const std::string mm::Serialized::get_str() const noexcept(false) {
    if (type != mm::TEXT) {
        throw std::runtime_error("ERROR [Serialized get_str] - the object is not TEXT!");
    }

    return std::string(data.text);
}

int mm::Serialized::get_int() const noexcept(false) {
    if (type != mm::INTEGER) {
        throw std::runtime_error("ERROR [Serialized get_str] - the object is not INTEGER!");
    }

    return data.integer;
}

double mm::Serialized::get_real() const noexcept(false) {
    if (type != mm::REAL) {
        throw std::runtime_error("ERROR [Serialized get_str] - the object is not REAL!");
    }

    return data.real;
}

mm::Serialized::Serialized(const char *c_str) noexcept
        : Serialized(std::string(c_str)) {}

mm::Serialized::operator int() const noexcept(false) {
    return get_int();
}

mm::Serialized::operator std::string() const noexcept(false) {
    return get_str();
}

mm::Serialized::operator double() const {
    return get_real();
}

mm::Serialized::Serialized(float data) noexcept
        : Serialized(static_cast<double>(data)) {}


