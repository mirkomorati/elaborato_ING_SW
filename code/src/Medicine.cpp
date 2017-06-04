/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#include "../hdr/Medicine.hpp"


map<string, mm::Serialized> mm::Medicine::serialize() const {
  map<string, mm::Serialized> map;
  mm::SerializedUnion tmp;
  tmp.text = name.c_str();
  map["name"] = mm::Serialized(mm::TEXT, tmp);
  tmp.real = price;
  map["price"] = mm::Serialized(mm::REAL, tmp);

  return map;
}

void mm::Medicine::unserialize(map<string, mm::Serialized> map1) {

}

string mm::Medicine::get_table_name() const {
  return "drugs";
}

string mm::Medicine::get_primary_key() const {
  return "name";
}

mm::Medicine::Medicine(const string &name, float price) : name(name),
                                                          price(price) {}
