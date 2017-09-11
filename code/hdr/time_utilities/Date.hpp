/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _DATE_H
#define _DATE_H

namespace mm {
    namespace util {
        struct Date {
            Date(int day, int month, int year);

            Date();

            int day;
            int month;
            int year;
        };
    }
}
#endif //_DATE_H