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

using namespace std;
struct Medicine {
    string name;
    float price;
    string pharmaceutical_form;
    vector<string> contraindications;
    string ATC_classification;
    vector<map<ActivePrinciple, string>> active_principles;
};

#endif //_MEDICINE_H