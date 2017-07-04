/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#include "../../hdr/model/Patient.hpp"

/**
 * Patient implementation
 */


mm::Patient::Patient() {

}

mm::Patient::~Patient() {

}

map<string, mm::Serialized> mm::Patient::serialize() const {
    return map<string, mm::Serialized>();
}

void mm::Patient::unserialize(map<string, mm::Serialized> map) {
    first_name = map["first_name"].get_str();
    last_name = map["last_name"].get_str();
    fiscal_code = map["fiscal_code"].get_str();
    health_code = map["health_code"].get_str();
    // TODO : Finire unserialize
}

string mm::Patient::get_table_name() const {
    return nullptr;
}

string mm::Patient::get_primary_key() const {
    return nullptr;
}

const string &mm::Patient::get_health_code() const {
    return health_code;
}

const string &mm::Patient::get_first_name() const {
    return first_name;
}

const string &mm::Patient::get_last_name() const {
    return last_name;
}

const mm::Date &mm::Patient::get_birth_date() const {
    return birth_date;
}

const Address &mm::Patient::get_birth_place() const {
    return birth_place;
}

const Address &mm::Patient::get_address() const {
    return address;
}

const vector<string> &mm::Patient::get_risk_factors() const {
    return risk_factors;
}

const string &mm::Patient::get_fiscal_code() const {
    return fiscal_code;
}
