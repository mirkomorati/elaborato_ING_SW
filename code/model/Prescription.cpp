/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#include <map>
#include <sstream>
#include "Prescription.hpp"
#include "../DBMaster.hpp"

mm::model::Prescription::TreeModel mm::model::Prescription::prescriptionTreeModel;

std::map<std::string, mm::Serialized> mm::model::Prescription::serialize() const {
    map<string, Serialized> serialized_map;
    serialized_map["patient_id"] = patient_id;
    serialized_map["prescription_id"] = prescription_id;
    serialized_map["issue_date"] = issue_date;
    serialized_map["expire_date"] = expire_date;
    stringstream ss;

    for (auto &it : drug_ids) {
        ss << it.first << ":" << it.second << ";";
    }

    ss.seekp(-1, ss.cur);
    serialized_map["drug_ids"] = ss.str();

    /*
    for (size_t i = 0; i < drug_ids.size(); i++) {
        drug_list << drug_ids[i];
        if (i < drug_ids.size() - 1) drug_list << ";";
    }
    */

    // serialized_map["drug_ids"] = drug_list.str();

    stringstream negative_interaction_list;
    for (auto row : negative_interactions) {
        negative_interaction_list << row.first << ":" << row.second << ";";
    }
    negative_interaction_list.seekp(-1, negative_interaction_list.cur);
    serialized_map["negative_interactions"] = negative_interaction_list.str();
    serialized_map["used"] = used ? "si" : "no";

    return serialized_map;
}

void mm::model::Prescription::unserialize(std::map<std::string, Serialized> map) {
    using namespace std;
    const char delimiter = ';';
    const char drug_ids_delimiter = ':';

    patient_id = map["patient_id"].get_int();
    prescription_id = map["prescription_id"].get_int();
    issue_date = map["issue_date"].get_str();
    expire_date = map["expire_date"].get_str();
    istringstream drug_list(map["drug_ids"].get_str());

    string tmp;

    while (getline(drug_list, tmp, delimiter)) {
        unsigned long pos = tmp.find(drug_ids_delimiter);
        if (pos == string::npos) drug_ids.emplace_back(tmp, "");
        else drug_ids.emplace_back(tmp.substr(0, pos), tmp.substr(pos + 1));
    }

    istringstream negative_interaction_list(map["negative_interactions"].get_str());
    while (getline(negative_interaction_list, tmp, ';')) {
        // todo questo è fatto male, molto male
        string delims = ":";
        vector<string> results;
        size_t lastOffset = 0;
        while (true) {
            size_t offset = tmp.find_first_of(delims, lastOffset);
            results.push_back(tmp.substr(lastOffset, offset - lastOffset));
            if (offset == string::npos)
                break;
            else
                lastOffset = offset + 1;
        }
        negative_interactions[results[0]] = results[1];
    }
    used = (map["used"].get_str() == "si");
}

string mm::model::Prescription::get_table_name() const {
    return "prescriptions";
}

vector<string> mm::model::Prescription::get_primary_key() const {
    return {"prescription_id"};
}

int mm::model::Prescription::get_patient_id() const {
    return patient_id;
}

int mm::model::Prescription::get_prescription_id() const {
    return prescription_id;
}

const string &mm::model::Prescription::get_issue_date() const {
    return issue_date;
}

const string &mm::model::Prescription::get_expire_date() const {
    return expire_date;
}

string mm::model::Prescription::get_drug_ids_as_string() {
    ostringstream ss;
    for (auto &it : drug_ids) {
        ss << it.first << ": " << it.second << "; ";
    }
    string ret = ss.str();
    ret = ret.substr(0, ret.length() - 2);
    return ret;
}

string mm::model::Prescription::get_negative_interactions() {
    ostringstream ss;
    for (auto row : negative_interactions) {
        ss << row.first << ": " << row.second << "; ";
    }
    string ret = ss.str();
    ret = ret.substr(0, ret.length() - 2);
    return ret;
}

bool mm::model::Prescription::is_used() const {
    return used;
}

int mm::model::Prescription::get_bill_id() const {
    return bill_id;
}

const vector<pair<string, string>> &mm::model::Prescription::get_drug_ids() const {
    return drug_ids;
}

const vector<mm::model::Drug> mm::model::Prescription::get_drugs() const {
    vector<Drug> toReturn;

    for (auto ids : drug_ids) {
        try {
            Drug tmp;
            DBMaster::get_instance().extract_from_db(tmp, {ids.first, ids.second});
            toReturn.push_back(std::move(tmp));
        } catch (record_not_found_error &e) {
            throw std::runtime_error("cannot get drug of a prescription");
        }
    }
    return toReturn;
}

mm::model::Prescription::TreeModel::TreeModel() {
    add(patient_id);
    add(issue_date);
    add(expire_date);
    add(drug_ids);
    add(prescription_id);
    add(negative_interactions);
    add(used);
    add(bill_id);
}
