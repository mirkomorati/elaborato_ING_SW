/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _PATIENT_H
#define _PATIENT_H

class Patient {
public: 
    
    void Patient();
    
    void ~Patient();
private: 
    string health_code;
    string first_name;
    string last_name;
    Date birth_date;
    Address birth_place;
    Address address;
    vector<string> risk_factors;
};

#endif //_PATIENT_H