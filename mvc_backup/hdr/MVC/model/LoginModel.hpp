//
// Created by Noè Murr on 02/07/2017.
//

#ifndef ELABORATO_ING_SW_LOGINMODEL_HPP
#define ELABORATO_ING_SW_LOGINMODEL_HPP

#include <vector>
#include "MainModel.hpp"

namespace mm {
    class MainModel;

    class LoginModel {
        MainModel *parent;

    public:
        std::vector<std::tuple<std::string, std::string, int>> get_login_data();
    };
}


#endif //ELABORATO_ING_SW_LOGINMODEL_HPP
