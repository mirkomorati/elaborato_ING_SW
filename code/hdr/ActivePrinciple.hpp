/**
 * Project Elaborato_ING_SW
 * @author Noè Murr, Mirko Morati
 */


#ifndef _ACTIVEPRINCIPLE_H
#define _ACTIVEPRINCIPLE_H

#include <string>
namespace mm {
  struct ActivePrinciple {
    friend std::ostream
    &operator<<(std::ostream &os, const ActivePrinciple &active_p);

    ActivePrinciple(const std::string &name, const std::string &description,
                    const std::string &effect);

    std::string name;
    std::string description;
    std::string effect;
  };

  std::ostream &operator<<(std::ostream &os, const ActivePrinciple &active_p);
}

#endif //_ACTIVEPRINCIPLE_H