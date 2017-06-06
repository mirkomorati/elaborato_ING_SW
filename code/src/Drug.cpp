/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#include <sstream>
#include <iostream>
#include "../hdr/Drug.hpp"


map<string, mm::Serialized> mm::Drug::serialize() const {
  map<string, mm::Serialized> map;
  std::stringstream ss;

  map["name"] = name;
  map["price"] = price;
  map["pharmaceutical_form"] = pharmaceutical_form;
  map["ATC_classification"] = ATC_classification;

  for (auto &it : active_principles) {
    for (auto &p : it){
      ss << p.first << ": " << p.second << std::endl;
    }
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
  // todo aggiungere un unserialize decente
  using namespace std;
  const string delimiter = "\n";

  name = map.at("name").get_str();
  price = (float) map.at("price").get_real();
  string cont_string = map.at("contraindications");

  size_t pos = 0;

  while ((pos = cont_string.find(delimiter)) != string::npos){
    contraindications.push_back(cont_string.substr(0, pos));
    cont_string.erase(0, pos + delimiter.length());
  }


}

string mm::Drug::get_table_name() const {
  return "drugs";
}

string mm::Drug::get_primary_key() const {
  return "name";
}

mm::Drug::Drug(const string &name, float price) : name(name), price(price) {}
