/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#include <iostream>
#include "../../hdr/model/Doctor.hpp"
#include "../../hdr/DBMaster.hpp"


map<string, mm::Serialized> mm::Doctor::serialize() const {
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

void mm::Doctor::unserialize(map<string, mm::Serialized> map) {
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

string mm::Doctor::get_table_name() const {
    return "doctors";
}

string mm::Doctor::get_primary_key() const {
    return "regional_id";
}

vector<mm::Prescription>
mm::Doctor::get_prescriptions(mm::Patient patient, mm::Date start,
                              mm::Date end) {
    return vector<mm::Prescription>();
}

vector<mm::Prescription>
mm::Doctor::get_prescriptions(mm::Drug drug) {
    return vector<mm::Prescription>();
}

vector<mm::Drug>
mm::Doctor::get_drugs(mm::Date start, mm::Date end) {
    return vector<mm::Drug>();
}

void mm::Doctor::get_patients_from_db() {
    auto rows = DBMaster::get_instance().get_rows("patients", "doctor_id", regional_id);

    for (auto &row : rows) {
        Patient tmp;
        tmp.unserialize(row);
        patients.push_back(tmp);
    }
}

vector<mm::Patient>
mm::Doctor::get_patients(mm::Drug drug) {
    return vector<mm::Patient>();
}

const string &mm::Doctor::get_fiscal_code() const {
    return fiscal_code;
}

const int &mm::Doctor::get_regional_id() const {
    return regional_id;
}

const string &mm::Doctor::get_specialization() const {
    return specialization;
}

vector<mm::Patient> &mm::Doctor::get_patients() {
    return patients;
}

const string &mm::Doctor::getFirst_name() const {
    return first_name;
}

const string &mm::Doctor::getLast_name() const {
    return last_name;
}

const string &mm::Doctor::getBirth_date() const {
    return birth_date;
}

const string &mm::Doctor::getBirth_place() const {
    return birth_place;
}
