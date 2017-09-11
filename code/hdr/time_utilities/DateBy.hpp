//
// Created by Mirko Morati on 11/09/17.
//

#ifndef ELABORATO_ING_SW_DATEBY_HPP
#define ELABORATO_ING_SW_DATEBY_HPP

#include <string>
#include "Date.hpp"

namespace mm {
    namespace util {
        struct DateBy {
            DateBy(Date date = {}, std::string by = "");

            Date date;
            std::string by;
        };
    }
}


#endif //ELABORATO_ING_SW_DATEBY_HPP
