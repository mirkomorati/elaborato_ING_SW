/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#include "../hdr/Drug.hpp"


map<string, mm::Serialized> mm::Drug::serialize() const {
  // todo serialize decente
  map<string, mm::Serialized> map;
  map["name"] = mm::Serialized(mm::TEXT, name);
  map["price"] = mm::Serialized(mm::REAL, price);

  return map;
}

void mm::Drug::unserialize(map<string, mm::Serialized> map) {
  // todo aggiungere un unserialize decente
  name = map["name"].get_str();
  price = (float) map["price"].get_real();
}

string mm::Drug::get_table_name() const {
  return "drugs";
}

string mm::Drug::get_primary_key() const {
  return "name";
}

mm::Drug::Drug(const string &name, float price) : name(name),
                                                          price(price) {}
