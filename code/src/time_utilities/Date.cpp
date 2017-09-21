/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#include "../../hdr/time_utilities/Date.hpp"
#include "../../hdr/string_utils/stringUtils.hpp"

/**
 * Date implementation
 */


mm::util::Date::Date(int day, int month, int year) : day(day), month(month), year(year) {
}

mm::util::Date::Date() : day(-1), month(-1), year(-1) {
}

std::ostream &mm::util::operator<<(std::ostream &os, const mm::util::Date &date) {
    os << date.day << "/" << date.month << "/" << date.year << std::endl;
    return os;
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

const std::string mm::util::Date::get_text() {
    using namespace std;
    stringstream ss;
    ss << day << "/" << month << "/" << year;
    return ss.str();
}

bool mm::util::Date::is_valid() {
    return (((day >= 1 and day <= 31) and
             (month == 1 or month == 3 or month == 5 or month == 7 or month == 8 or month == 10 or month == 12)))
           or (((day >= 1 and day <= 30) and (month == 4 or month == 6 or month == 9 or month == 11)))
           or (((day >= 1 and day <= 28) and (month == 2)))
           or ((day == 29 and month == 2 and (year % 400 == 0 or (year % 4 == 0 and year % 100 != 0))));
}

int mm::util::Date::get_current_year() {

    std::time_t t = std::time(nullptr);
    std::tm *time_p = std::localtime(&t);
    time_p->tm_year;
}

int mm::util::Date::get_current_day() {
    std::time_t t = std::time(nullptr);
    std::tm *time_p = std::localtime(&t);
    time_p->tm_mday;
}

int mm::util::Date::get_current_month() {
    std::time_t t = std::time(nullptr);
    std::tm *time_p = std::localtime(&t);
    time_p->tm_mon;
}
