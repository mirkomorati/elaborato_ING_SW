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

            Date(const std::string &str);

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

            void add_months(unsigned int months);

            void add_years(unsigned int years);

            int day;
            int month;
            int year;

            static int get_current_day();

            static int get_current_month();

            static int get_current_year();

            static Date get_current_date();

            static inline bool is_leap_year(int year) {
                return (year % 4 == 0 and year % 100 != 0) or year % 400 == 0;
            };
        };
    }
}
#endif //_DATE_H