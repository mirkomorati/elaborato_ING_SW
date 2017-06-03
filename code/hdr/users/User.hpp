/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _USER_H
#define _USER_H

#include "../time_utilities/Date.hpp"
#include "../Address.hpp"
#include <string>

class User {
private: 
    std::string first_name;
    std::string last_name;
    Date birth_date;
    Address birth_place;
};

#endif //_USER_H