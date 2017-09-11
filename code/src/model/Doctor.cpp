/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#include <iostream>
#include "../../hdr/model/Doctor.hpp"
#include "../../hdr/DBMaster.hpp"


map<string, mm::Serialized> mm::model::Doctor::serialize() const {
    map<string, mm::Serialized> serialized;
    serialized["regional_id"] = regional_id;
    serialized["fiscal_code"] = fiscal_code;
    serialized["first_name"] = first_name;
    serialized["last_name"] = last_name;
    serialized["fiscal_code"] = fiscal_code;
    serialized["birth_place"] = birth_place;
    serialized["birth_place"] = birth_place;

    return serialized;
}

void mm::model::Doctor::unserialize(map<string, mm::Serialized> map) {
    regional_id = map["regional_id"].get_int();
    fiscal_code = map["fiscal_code"].get_str();
    specialization = map["specialization"].get_str();
    first_name = map["first_name"].get_str();
    last_name = map["last_name"].get_str();
    fiscal_code = map["fiscal_code"].get_str();
    birth_place = map["birth_place"].get_str();
    birth_place = map["birth_place"].get_str();
    get_patients_from_db();
}

string mm::model::Doctor::get_table_name() const {
    return "doctors";
}

string mm::model::Doctor::get_primary_key() const {
    return "regional_id";
}

vector<mm::model::Prescription>
mm::model::Doctor::get_prescriptions(mm::model::Patient patient, mm::util::Date start,
                                     mm::util::Date end) {
    return vector<mm::model::Prescription>();
}

vector<mm::model::Prescription>
mm::model::Doctor::get_prescriptions(mm::model::Drug drug) {
    return vector<mm::model::Prescription>();
}

vector<mm::model::Drug>
mm::model::Doctor::get_drugs(mm::util::Date start, mm::util::Date end) {
    return vector<mm::model::Drug>();
}

void mm::model::Doctor::get_patients_from_db() {
    auto rows = DBMaster::get_instance().get_rows("patients", "doctor_id", regional_id);

    for (auto &row : rows) {
        Patient tmp;
        tmp.unserialize(row);
        patients.push_back(tmp);
    }
}

vector<mm::model::Patient>
mm::model::Doctor::get_patients(mm::model::Drug drug) {
    return vector<mm::model::Patient>();
}

const string &mm::model::Doctor::get_fiscal_code() const {
    return fiscal_code;
}

const int &mm::model::Doctor::get_regional_id() const {
    return regional_id;
}

const string &mm::model::Doctor::get_specialization() const {
    return specialization;
}

vector<mm::model::Patient> &mm::model::Doctor::get_patients() {
    return patients;
}

const string &mm::model::Doctor::get_first_name() const {
    return first_name;
}

const string &mm::model::Doctor::get_last_name() const {
    return last_name;
}

const string &mm::model::Doctor::get_birth_date() const {
    return birth_date;
}

const string &mm::model::Doctor::get_birth_place() const {
    return birth_place;
}
