/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _DATE_H
#define _DATE_H

#include <iostream>

namespace mm {
    namespace util {
        struct Date {
            Date(int day, int month, int year);

            Date();

            friend std::ostream &operator<<(std::ostream &os, const Date &date);

            int day;
            int month;
            int year;
        };

        std::ostream &operator<<(std::ostream &os, const Date &date);
    }
}
#endif //_DATE_H