//
// Created by Noè Murr on 02/07/2017.
//

#ifndef ELABORATO_ING_SW_LOGINMODEL_HPP
#define ELABORATO_ING_SW_LOGINMODEL_HPP

#include <vector>

namespace mm {
    class LoginModel {

    public:
        std::vector<std::tuple<std::string, std::string, int>> getLoginData();
    };
}


#endif //ELABORATO_ING_SW_LOGINMODEL_HPP
