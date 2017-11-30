/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#include <sstream>
#include "Patient.hpp"
#include "../DBMaster.hpp"

mm::model::Patient::Patient() {

}

mm::model::Patient::~Patient() {

}

map<string, mm::Serialized> mm::model::Patient::serialize() const {
    map<string, Serialized> serialized_map;
    serialized_map["first_name"] = first_name;
    serialized_map["last_name"] = last_name;
    serialized_map["fiscal_code"] = fiscal_code;
    serialized_map["health_code"] = health_code;
    serialized_map["address"] = address;
    serialized_map["birth_date"] = birth_date;
    serialized_map["birth_place"] = birth_place;
    serialized_map["doctor_id"] = doctor_id;
    stringstream risk_list;
    for (size_t i = 0; i < risk_factors.size(); i++) {
        risk_list << risk_factors[i];
        if (i < risk_factors.size() - 1) risk_list << ";";
    }
    serialized_map["risk_factors"] = risk_list.str();

    return serialized_map;
}

void mm::model::Patient::unserialize(map<string, mm::Serialized> map) {
    first_name = map["first_name"].get_str();
    last_name = map["last_name"].get_str();
    fiscal_code = map["fiscal_code"].get_str();
    health_code = map["health_code"].get_str();
    address = map["address"].get_str();
    birth_date = map["birth_date"].get_str();
    birth_place = map["birth_place"].get_str();
    doctor_id = map["doctor_id"].get_int();
    istringstream risk_list(map["risk_factors"].get_str());
    string tmp;
    while (getline(risk_list, tmp, ';')) {
        risk_factors.push_back(tmp);
    }
    get_prescriptions_from_db();
}

string mm::model::Patient::get_table_name() const {
    return "patients";
}

vector<string> mm::model::Patient::get_primary_key() const {
    return {"health_code"};
}

const string &mm::model::Patient::get_health_code() const {
    return health_code;
}

const string &mm::model::Patient::get_first_name() const {
    return first_name;
}

const string &mm::model::Patient::get_last_name() const {
    return last_name;
}

const string &mm::model::Patient::get_birth_date() const {
    return birth_date;
}

const string &mm::model::Patient::get_birth_place() const {
    return birth_place;
}

const string &mm::model::Patient::get_address() const {
    return address;
}

string mm::model::Patient::get_risk_factors() const {
    ostringstream ss;
    copy(risk_factors.begin(), risk_factors.end(),
         ostream_iterator<string>(ss, ", "));
    string ret = ss.str();
    return ret;
}

const string &mm::model::Patient::get_fiscal_code() const {
    return fiscal_code;
}

void mm::model::Patient::get_prescriptions_from_db() {
    auto rows = DBMaster::get_instance().get_rows("prescriptions", "patient_id",
                                                  health_code);
    for (auto &row : rows) {
        Prescription tmp;
        tmp.unserialize(row);
        prescriptions.push_back(tmp);
    }
}

vector<mm::model::Prescription> &mm::model::Patient::get_prescriptions() {
    return prescriptions;
}

void mm::model::Patient::set_health_code(const string &health_code) {
    this->health_code = health_code;
}

void mm::model::Patient::set_first_name(const string &first_name) {
    this->first_name = first_name;
}

void mm::model::Patient::set_last_name(const string &last_name) {
    this->last_name = last_name;
}

void mm::model::Patient::set_fiscal_code(const string &fiscal_code) {
    this->fiscal_code = fiscal_code;
}

void mm::model::Patient::set_birth_date(const string &birth_date) {
    this->birth_date = birth_date;
}

void mm::model::Patient::set_birth_place(const string &birth_place) {
    this->birth_place = birth_place;
}

void mm::model::Patient::set_address(const string &address) {
    this->address = address;
}

void mm::model::Patient::set_doctor_id(int doctor_id) {
    this->doctor_id = doctor_id;
}

int mm::model::Patient::get_doctor_id() const {
    return doctor_id;
}

bool mm::model::Patient::operator==(const mm::model::Patient &rhs) const {
    return health_code == rhs.health_code;
}

bool mm::model::Patient::operator!=(const mm::model::Patient &rhs) const {
    return !(rhs == *this);
}

bool mm::model::Patient::is_valid() {
    return !first_name.empty() && !last_name.empty() && !fiscal_code.empty()
           && !birth_date.empty() && !birth_place.empty() && !address.empty()
           && doctor_id != 0 && !health_code.empty();
}

mm::model::Patient::TreeModel::TreeModel() {
    add(first_name);
    add(last_name);
    add(fiscal_code);
    add(health_code);
    add(birth_date);
    add(birth_place);
    add(address);
    add(risk_factors);
}