/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _USER_H
#define _USER_H

#include "../time_utilities/Date.hpp"
#include "../Address.hpp"
#include "../interfaces/ISerializable.hpp"
#include <string>


namespace mm {
    class User : public mm::ISerializable {
    private:
        std::string first_name;
        std::string last_name;
        util::Date birth_date;
        Address birth_place;
    };
}

#endif //_USER_H