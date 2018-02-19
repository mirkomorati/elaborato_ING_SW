//
// Created by Mirko Morati on 11/09/17.
//

#ifndef ELABORATO_ING_SW_DATEBY_HPP
#define ELABORATO_ING_SW_DATEBY_HPP

#include <string>
#include <ostream>
#include "Date.hpp"

namespace mm {
    namespace util {
        struct DateBy {
            DateBy(Date date = {}, std::string by = "");

            friend std::ostream &operator<<(std::ostream &os, const DateBy &by);

            Date date;
            std::string by;
        };

        std::ostream &operator<<(std::ostream &os, const DateBy &by);
    }
}


#endif //ELABORATO_ING_SW_DATEBY_HPP
