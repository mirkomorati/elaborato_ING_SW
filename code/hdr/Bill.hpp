/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _BILL_H
#define _BILL_H

class Bill {
public: 
    Pharmacist pharmacist;
    vector<map<int, bool>> medicines;
    float subtotal;
    Date date;
    Time time;
    int prescription_id;
};

#endif //_BILL_H