//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_LOGINCONTROLLER_HPP
#define ELABORATO_ING_SW_LOGINCONTROLLER_HPP

#include "../view/LoginView.hpp"

namespace mm {
    class LoginView;

    class LoginController {

    public:
        void set_view(LoginView &view);
    };
}

#endif //ELABORATO_ING_SW_LOGINCONTROLLER_HPP
