/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#include <sstream>
#include <iostream>
#include <iomanip>
#include "../../hdr/model/Drug.hpp"


map<string, mm::Serialized> mm::model::Drug::serialize() const {
    map<string, mm::Serialized> map;
    std::stringstream ss;

    map["name"] = name;
    map["price"] = price;
    map["pharmaceutical_form"] = pharmaceutical_form;
    map["ATC_classification"] = ATC_classification;

    for (auto &it : active_principles) {
        ss << it.first << ":" << it.second << ";";
    }
    ss.seekp(-1, ss.cur);
    map["active_principles"] = ss.str();

    ss.str("");
    for (auto &c : contraindications) {
        ss << c << std::endl;
    }

    map["contraindications"] = ss.str();


    return map;
}

void mm::model::Drug::unserialize(map<string, mm::Serialized> map) {
    using namespace std;
    const char delimiter = ';';
    const char active_principle_delimiter = ':';

    name = map.at("name").get_str();
    price = (float) map.at("price").get_real();
    pharmaceutical_form = map.at("pharmaceutical_form").get_str();
    ATC_classification = map.at("ATC_classification").get_str();
    istringstream cont_string(map.at("contraindications").get_str());
    istringstream active_principle_str(map.at("active_principles").get_str());

    string tmp;
    while (getline(cont_string, tmp, delimiter)) {
        contraindications.push_back(tmp);
    }

    while (getline(active_principle_str, tmp, delimiter)) {
        unsigned long pos = tmp.find(active_principle_delimiter);
        if (pos == string::npos) active_principles.emplace_back(tmp, "");
        else active_principles.emplace_back(tmp.substr(0, pos), tmp.substr(pos + 1));
    }
}

string mm::model::Drug::get_table_name() const {
    return "drugs";
}

vector<string> mm::model::Drug::get_primary_key() const {
    return {"name", "pharmaceutical_form"};
}

mm::model::Drug::Drug(const string &name, float price) : name(name), price(price) {}

const string &mm::model::Drug::get_name() const {
    return name;
}

float mm::model::Drug::get_price() const {
    return price;
}

const string &mm::model::Drug::get_pharmaceutical_form() const {
    return pharmaceutical_form;
}

const vector<string> &mm::model::Drug::get_contraindications() const {
    return contraindications;
}

const string mm::model::Drug::get_ATC_classification() const {
    return ATC_classification;
}

const vector<pair<string, string>> &mm::model::Drug::get_active_principles() const {
    return active_principles;
}

const string mm::model::Drug::get_contraindications_as_string() const {
    ostringstream ss;
    if (contraindications.empty()) return "ERROR empty";
    copy(contraindications.begin(), contraindications.end(), ostream_iterator<string>(ss, ", "));
    string ret = ss.str();
    ret = ret.substr(0, ret.length() - 2);
    return ret;
}

const string mm::model::Drug::get_active_principles_as_string() const {
    ostringstream ss;
    if (active_principles.empty()) return "ERROR empty";
    for (auto &p : active_principles) {
        ss << p.first << ", " << p.second << std::endl;
    }
    string ret = ss.str();
    return ret;
}

mm::model::Drug::Drug() {}

const string mm::model::Drug::get_price_as_string() const {
    std::stringstream ss;
    ss << std::setw(2) << price;
    return ss.str();
}

mm::model::Drug::TreeModel::TreeModel() {
    add(name);
    add(pharmaceutical_form);
    add(ATC_classification);
    add(contraindications);
    add(active_principles);
    add(price);
}