//
// Created by Mirko Morati on 04/07/17.
//

#ifndef ELABORATO_ING_SW_LOGINMODEL_HPP
#define ELABORATO_ING_SW_LOGINMODEL_HPP

#include "DBMaster.hpp"
#include <vector>
#include <tuple>

namespace mm {
    class LoginModel {
    public:
        std::vector<std::tuple<std::string, std::string, int>> get_login_data();
    };
}


#endif //ELABORATO_ING_SW_LOGINMODEL_HPP
