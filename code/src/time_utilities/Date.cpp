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
