//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_LOGINVIEW_HPP
#define ELABORATO_ING_SW_LOGINVIEW_HPP

#include "../controller/Login.hpp"
#include "Main.hpp"
#include <gtkmm-3.0/gtkmm.h>

namespace mm {
    namespace controller {
        class Login;
    }

    namespace view {
        class Main;

        class Login {
        public:
            explicit Login();

            void login_update(bool success);

            void set_parent(view::Main *parent);

        private:
            view::Main *parent;
            controller::Login *controller;

            Gtk::Button *button;
        };
    }
}


#endif //ELABORATO_ING_SW_LOGINVIEW_HPP
