/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _BILL_H
#define _BILL_H

#include "users/Pharmacist.hpp"
#include "time_utilities/Date.hpp"
#include "time_utilities/Time.hpp"
#include <map>
#include <vector>

using namespace std;
struct Bill {

    Pharmacist pharmacist;
    vector<map<int, bool>> medicines;
    float subtotal;
    Date date;
    Time time;
    int prescription_id;
};

#endif //_BILL_H