//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_LOGIN_CONTROLLER_HPP
#define ELABORATO_ING_SW_LOGIN_CONTROLLER_HPP

#include "../view/Login.hpp"
#include <gdk/gdk.h>

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

            void set_parent(controller::Main *parent);

            bool key_pressed_handler(GdkEventKey *event);

        private:
            view::Login *view;
            controller::Main *parent;
        };
    }
}

#endif //ELABORATO_ING_SW_LOGIN_CONTROLLER_HPP
