/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _ADDRESS_H
#define _ADDRESS_H

#include <string>

struct Address {
    std::string street_address;
    std::string civic_number;
    std::string zip_code;
    std::string city;
    std::string country;
};

#endif //_ADDRESS_H