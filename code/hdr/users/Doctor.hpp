/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _DOCTOR_H
#define _DOCTOR_H

#include "User.hpp"


class Doctor: public User {
private: 
    string fiscal_code;
    string regional_id;
    string specialization;
    vector<int> prescriptions_id;
};

#endif //_DOCTOR_H