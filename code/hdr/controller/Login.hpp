//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_LOGIN_CONTROLLER_HPP
#define ELABORATO_ING_SW_LOGIN_CONTROLLER_HPP

#include "../view/Login.hpp"

namespace mm {
    namespace view {
        class Login;
    }

    namespace controller {
        class Main;

        class Login {
        public:
            void set_view(view::Login *view);

            void login_button_handler();

        private:
            view::Login *view;
        };
    }
}

#endif //ELABORATO_ING_SW_LOGIN_CONTROLLER_HPP
