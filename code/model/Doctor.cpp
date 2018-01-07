/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#include <iostream>
#include <algorithm>
#include "Doctor.hpp"
#include "../DBMaster.hpp"


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

vector<string> mm::model::Doctor::get_primary_key() const {
    return {"regional_id"};
}

vector<mm::model::Prescription>
mm::model::Doctor::get_prescriptions(mm::model::Patient patient, mm::util::Date start,
                                     mm::util::Date end) {
    vector<Prescription> to_ret;

    if (patient.is_valid()) {
        if (std::find(patients.begin(), patients.end(), patient) == patients.end()) {
            throw std::invalid_argument("the patients does not belong to the doctor");
        }

        for (auto &pr : patient.get_prescriptions()) {
            to_ret.push_back(pr);
        }
    } else {
        for (const auto &p : patients) {
            to_ret.reserve(to_ret.size() + p.get_prescriptions().size());
            for (const auto &pr : p.get_prescriptions()) {
                to_ret.push_back(pr);
            }
        }
    }

    if (end > start) {
        for (auto it = to_ret.begin(); it != to_ret.end(); ++it) {
            mm::util::Date tmp_date;
            tmp_date.set_from_str(it->get_issue_date());
            if (tmp_date < start and tmp_date > end)
                to_ret.erase(it);
        }
    }

    return to_ret;
}

vector<mm::model::Prescription>
mm::model::Doctor::get_prescriptions(mm::model::Drug drug) {
    vector<Prescription> to_ret;

    // todo aggiungere un operatore di uguaglianza a Drug per poterli confrontare.
    // N.B. qui è necessario un accesso al db.
    return to_ret;
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

mm::model::Patient mm::model::Doctor::get_patient_from_fiscal_code(std::string fiscal_code) {
    for (auto &p : patients) {
        if (p.get_fiscal_code() == fiscal_code)
            return p;
    }

    throw std::runtime_error("patient not found");
}
