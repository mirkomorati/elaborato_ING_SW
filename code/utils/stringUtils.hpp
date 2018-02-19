//
// Created by Noè Murr on 06/09/2017.
//

#ifndef STRINGUTILS_ELABORATO_HPP
#define STRINGUTILS_ELABORATO_HPP

#include <string>
#include <sstream>
#include <vector>
#include <iterator>

namespace mm {
    namespace util {
        namespace str {
            template<typename Out>
            void split(const std::string &s, char delim, Out result, bool skipEmpty = false) {
                std::stringstream ss;
                ss.str(s);
                std::string item;
                while (std::getline(ss, item, delim)) {
                    if (skipEmpty and item.empty()) continue;
                    *(result++) = item;
                }
            }

            inline std::vector<std::string> split(const std::string &s, char delim, bool skipEmpty = false) {
                using namespace std;
                vector<string> elems;
                split(s, delim, back_inserter(elems), skipEmpty);
                return elems;
            }
        }
    }
}


#endif //STRINGUTILS_ELABORATO_HPP
