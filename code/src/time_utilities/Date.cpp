/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#include "../../hdr/time_utilities/Date.hpp"

/**
 * Date implementation
 */


mm::util::Date::Date(int day, int month, int year) : day(day), month(month), year(year) {
}

mm::util::Date::Date() : day(-1), month(-1), year(-1) {
}