//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_LOGINVIEW_HPP
#define ELABORATO_ING_SW_LOGINVIEW_HPP

#include "../controller/LoginController.hpp"

namespace mm {
    class LoginController;

    class LoginView {
    public:
        LoginView(LoginController controller);

    private:
        LoginController &controller;

    };
}


#endif //ELABORATO_ING_SW_LOGINVIEW_HPP
