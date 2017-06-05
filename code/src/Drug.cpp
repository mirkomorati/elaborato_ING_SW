/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#include "../hdr/Drug.hpp"


map<string, mm::Serialized> mm::Drug::serialize() const {
  map<string, mm::Serialized> map;
  mm::SerializedUnion tmp;
  tmp.text = name.c_str();
  map["name"] = mm::Serialized(mm::TEXT, tmp);
  tmp.real = price;
  map["price"] = mm::Serialized(mm::REAL, tmp);

  return map;
}

void mm::Drug::unserialize(map<string, mm::Serialized> map1) {

}

string mm::Drug::get_table_name() const {
  return "drugs";
}

string mm::Drug::get_primary_key() const {
  return "name";
}

mm::Drug::Drug(const string &name, float price) : name(name),
                                                          price(price) {}
