/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#include "Date.hpp"
#include "stringUtils.hpp"
#include <ctime>

/**
 * Date implementation
 */


mm::util::Date::Date(int day, int month, int year) : day(day), month(month), year(year) {
}

mm::util::Date::Date() : day(-1), month(-1), year(-1) {
}

void mm::util::Date::set_from_str(std::string str) {
    auto token_vector = str::split(str, '/');
    if (token_vector.size() != 3) throw std::invalid_argument("format must be dd/mm/yyyy");

    day = std::stoi(token_vector[0]);
    month = std::stoi(token_vector[1]);
    year = std::stoi(token_vector[2]);
}

bool mm::util::Date::operator==(const mm::util::Date &rhs) const {
    return day == rhs.day &&
           month == rhs.month &&
           year == rhs.year;
}

bool mm::util::Date::operator!=(const mm::util::Date &rhs) const {
    return !(rhs == *this);
}

bool mm::util::Date::operator<(const mm::util::Date &rhs) const {
    return not(*this >= rhs);
}

bool mm::util::Date::operator>(const mm::util::Date &rhs) const {
    return not(*this <= rhs);
}

bool mm::util::Date::operator<=(const mm::util::Date &rhs) const {
    if (year < rhs.year) return true;
    else if (year > rhs.year) return false;
    else {
        if (month < rhs.month) return true;
        else if (month > rhs.month) return false;
        else {
            return day <= rhs.day;
        }
    }
}

bool mm::util::Date::operator>=(const mm::util::Date &rhs) const {
    if (year > rhs.year) return true;
    else if (year < rhs.year) return false;
    else {
        if (month > rhs.month) return true;
        else if (month < rhs.month) return false;
        else {
            return day >= rhs.day;
        }
    }
}

const std::string mm::util::Date::get_as_text() {
    using namespace std;
    stringstream ss;
    ss << (day < 10 ? "0" : "") << day << "/" << (month < 10 ? "0" : "") << month << "/" << year;
    return ss.str();
}

bool mm::util::Date::is_valid() {
    return (day > 0 and month > 0 and year > 0) and
           ((((day >= 1 and day <= 31) and
              (month == 1 or month == 3 or month == 5 or month == 7 or month == 8 or month == 10 or month == 12))) or
            ((day >= 1 and day <= 30) and (month == 4 or month == 6 or month == 9 or month == 11)) or
            ((day >= 1 and day <= 28) and (month == 2)) or
            ((day == 29 and month == 2 and (year % 400 == 0 or (year % 4 == 0 and year % 100 != 0)))));
}

int mm::util::Date::get_current_year() {
    std::time_t t = std::time(nullptr);
    std::tm *time_p = std::localtime(&t);
    return time_p->tm_year + 1900;
}

int mm::util::Date::get_current_day() {
    std::time_t t = std::time(nullptr);
    std::tm *time_p = std::localtime(&t);
    return time_p->tm_mday;
}

int mm::util::Date::get_current_month() {
    std::time_t t = std::time(nullptr);
    std::tm *time_p = std::localtime(&t);
    return time_p->tm_mon + 1;
}

void mm::util::Date::operator+=(int days) {
    int days_per_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    day += days;
    while (day > days_per_month[month]) {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            days_per_month[2] = 29;
        }
        day -= days_per_month[month];
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
}

mm::util::Date mm::util::Date::operator+(int days) {
    int days_per_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    day += days;
    while (day > days_per_month[month]) {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            days_per_month[2] = 29;
        }
        day -= days_per_month[month];
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
    return {day, month, year};
}

mm::util::Date mm::util::Date::get_current_date() {
    return {util::Date::get_current_day(), util::Date::get_current_month(), util::Date::get_current_year()};
}

mm::util::Date::Date(const std::string &str) {
    set_from_str(str);
}

void mm::util::Date::add_months(unsigned int months) {
    int days_per_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (is_leap_year(year)) days_per_month[2] = 28;

    while (months > 0) {
        if (++month > 12) {
            if (is_leap_year(++year)) days_per_month[2] = 28;
            else days_per_month[2] = 29;
            month = 1;
        } else {
            if (day > days_per_month[month]) {
                day -= days_per_month[month];
                ++month;
            }
        }
        --months;
    }
}

void mm::util::Date::add_years(unsigned int years) {
    add_months(years * 12);
}
