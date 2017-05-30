/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _PHARMACIST_H
#define _PHARMACIST_H

#include "User.hpp"


class Pharmacist: public User {
public: 
    
    Bill Sell();
    
    void Order();
};

#endif //_PHARMACIST_H