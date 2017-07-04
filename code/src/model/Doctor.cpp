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
    serialized["specialization"] = specialization;

    return serialized;
}

void mm::Doctor::unserialize(map<string, mm::Serialized> map) {
    regional_id = static_cast<int>(map["regional_id"]);
    fiscal_code = static_cast<string>(map["fiscal_code"]);
    specialization = static_cast<string>(map["specialization"]);
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
    return vector<mm::Prescription, allocator<mm::Prescription>>();
}

vector<mm::Prescription, allocator<mm::Prescription>>
mm::Doctor::get_prescriptions(mm::Drug drug) {
    return vector<mm::Prescription, allocator<mm::Prescription>>();
}

vector<mm::Drug, allocator<mm::Drug>>
mm::Doctor::get_drugs(mm::Date start, mm::Date end) {
    return vector<mm::Drug, allocator<mm::Drug>>();
}

void mm::Doctor::get_patients_from_db() {
    auto rows = DBMaster::get_instance().get_rows("patients", "doctor_id", regional_id);

    for (auto &row : rows) {
        Patient tmp;
        tmp.unserialize(row);
        patients.push_back(tmp);
    }
}

vector<mm::Patient, allocator<mm::Patient>>
mm::Doctor::get_patients(mm::Drug drug) {
    return vector<mm::Patient, allocator<mm::Patient>>();
}

const string &mm::Doctor::getFiscal_code() const {
    return fiscal_code;
}

const int &mm::Doctor::getRegional_id() const {
    return regional_id;
}

const string &mm::Doctor::getSpecialization() const {
    return specialization;
}

vector<mm::Patient> &mm::Doctor::get_patients() {
    return patients;
}
