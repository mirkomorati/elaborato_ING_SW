//
// Created by Noè Murr on 22/09/2017.
//

#ifndef ELABORATO_ING_SW_MAIN_HPP
#define ELABORATO_ING_SW_MAIN_HPP

#include <utility>

namespace mm {
    namespace model {

        enum StackPage {
            LOGIN,
            APPLICATION,
        };

        struct Main {
            std::pair<StackPage, bool> stackPage;
            std::pair<bool, bool> login_failed;
        };
    }
}


#endif //ELABORATO_ING_SW_MAIN_HPP
