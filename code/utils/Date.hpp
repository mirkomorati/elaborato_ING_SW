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

            void set_from_str(std::string str);

            const std::string get_as_text();

            bool is_valid();

            bool operator==(const Date &rhs) const;

            bool operator!=(const Date &rhs) const;

            bool operator<(const Date &rhs) const;

            bool operator>(const Date &rhs) const;

            bool operator<=(const Date &rhs) const;

            bool operator>=(const Date &rhs) const;

            void operator+=(int days);

            Date operator+(int days);

            friend std::ostream &operator<<(std::ostream &os, const Date &date) {
                os << date.day << "/" << (date.month < 10 ? "0" : "") << date.month << "/" << date.year << std::endl;
                return os;
            }

            int day;
            int month;
            int year;

            static int get_current_day();

            static int get_current_month();

            static int get_current_year();

            static Date get_current_date();
        };
    }
}
#endif //_DATE_H