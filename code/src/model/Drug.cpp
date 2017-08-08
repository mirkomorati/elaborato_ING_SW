/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#include <sstream>
#include <iostream>
#include "../../hdr/model/Drug.hpp"


map<string, mm::Serialized> mm::model::Drug::serialize() const {
    map<string, mm::Serialized> map;
    std::stringstream ss;

    map["name"] = name;
    map["price"] = price;
    map["pharmaceutical_form"] = pharmaceutical_form;
    map["ATC_classification"] = ATC_classification;

    for (auto &it : active_principles) {
        ss << it.first << ": " << it.second << std::endl;
    }

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
    const string delimiter = "\n";
    const string principles_spacer = ": ";
    size_t pos = 0;

    name = map.at("name").get_str();
    price = (float) map.at("price").get_real();
    pharmaceutical_form = map.at("pharmaceutical_form").get_str();
    ATC_classification = map.at("ATC_classification").get_str();
    string cont_string = map.at("contraindications");
    string active_principle_str = map.at("active_principles");

    while ((pos = cont_string.find(delimiter)) != string::npos) {
        contraindications.push_back(cont_string.substr(0, pos));
        cont_string.erase(0, pos + delimiter.length());
    }

    pos = 0;

    while ((pos = active_principle_str.find(delimiter)) != string::npos) {
        size_t spacer_pos;
        string actual_principle;

        actual_principle = active_principle_str.substr(0, pos); // until \n
        spacer_pos = actual_principle.find(principles_spacer);

        active_principles.push_back(
                {actual_principle.substr(0, spacer_pos),
                 actual_principle.substr(spacer_pos + principles_spacer.length())});


        active_principle_str.erase(0, pos + delimiter.length());
    }

}

string mm::model::Drug::get_table_name() const {
    return "drugs";
}

string mm::model::Drug::get_primary_key() const {
    return "name";
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
    // todo sistemare unserialize o capire perché è vuoto
    if (contraindications.empty()) return "ERROR empty";
    copy(contraindications.begin(), contraindications.end(), ostream_iterator<string>(ss, ", "));
    string ret = ss.str();
    ret = ret.substr(0, ret.length() - 2);
    return ret;
}

const string mm::model::Drug::get_active_principles_as_string() const {
    ostringstream ss;
    // todo sistemare unserialize o capire perché è vuoto
    if (active_principles.empty()) return "ERROR empty";
    for (auto &p : active_principles) {
        ss << p.first << ", " << p.second;
    }
    string ret = ss.str();
    ret = ret.substr(0, ret.length() - 2);
    return ret;
}

mm::model::Drug::Drug() {}

mm::model::Drug::TreeModel::TreeModel() {
    add(name);
    add(pharmaceutical_form);
    add(ATC_classification);
    add(contraindications);
    add(active_principles);
    add(price);
}