/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _PRESCRIPTION_H
#define _PRESCRIPTION_H

#include <vector>
#include <string>
#include <map>

#include "time_utilities/Date.hpp"

using namespace std;

struct Prescription {
    int patient_id;
    Date issue_date;
    Date expiry_date;
    vector<int> medicines_id;
    string id;
    vector<map<int, int>> negative_interactions;
    bool used;
    int bill_id;
};

#endif //_PRESCRIPTION_H