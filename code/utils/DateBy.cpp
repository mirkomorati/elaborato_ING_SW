//
// Created by Mirko Morati on 11/09/17.
//

#include "DateBy.hpp"

mm::util::DateBy::DateBy(Date date, std::string by) : date(date), by(by) {
}

std::ostream &mm::util::operator<<(std::ostream &os, const mm::util::DateBy &by) {
    os << "date: " << by.date << " by: " << by.by;
    return os;
}
