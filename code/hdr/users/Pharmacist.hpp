/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _PHARMACIST_H
#define _PHARMACIST_H

#include "User.hpp"
#include "../Bill.hpp"

struct Bill;

class Pharmacist: public User {
public: 
    
    Bill Sell();
    
    void Order();
};

#endif //_PHARMACIST_H