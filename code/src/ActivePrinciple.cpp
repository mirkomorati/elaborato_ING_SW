/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#include "../hdr/ActivePrinciple.hpp"

/**
 * ActivePrinciple implementation
 */
std::ostream &
mm::operator<<(std::ostream &os, const mm::ActivePrinciple &active_p) {
  return os << active_p.name;
}

mm::ActivePrinciple::ActivePrinciple(const std::string &name,
                                     const std::string &description,
                                     const std::string &effect)
    : name(name), description(description), effect(effect) {}
