/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#include <sstream>
#include <iostream>
#include "../../hdr/model/Drug.hpp"


map<string, mm::Serialized> mm::Drug::serialize() const {
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

void mm::Drug::unserialize(map<string, mm::Serialized> map) {
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

string mm::Drug::get_table_name() const {
    return "drugs";
}

string mm::Drug::get_primary_key() const {
    return "name";
}

mm::Drug::Drug(const string &name, float price) : name(name), price(price) {}
