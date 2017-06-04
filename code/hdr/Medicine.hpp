/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _MEDICINE_H
#define _MEDICINE_H

#include <string>
#include <vector>
#include <map>
#include "ActivePrinciple.hpp"
#include "../hdr/interfaces/ISerializable.hpp"

using namespace std;
namespace mm {
  struct Medicine : ISerializable {
    string name;
    float price;
    string pharmaceutical_form;
    vector<string> contraindications;
    string ATC_classification;
    vector<map<ActivePrinciple, string>> active_principles;

  public:
    Medicine(const string &name, float price);

    map<string, Serialized> serialize() const override;

    void unserialize(map<string, Serialized> map1) override;

    string get_table_name() const override;

    string get_primary_key() const override;
  };
}

#endif //_MEDICINE_H