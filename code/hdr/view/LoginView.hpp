//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_LOGINVIEW_HPP
#define ELABORATO_ING_SW_LOGINVIEW_HPP

#include "../controller/LoginController.hpp"
#include <gtkmm-3.0/gtkmm.h>

namespace mm {
    class LoginController;

    class LoginView {
    public:
        LoginView(LoginController &controller);

        void login_update(int doctor_id);

    private:
        LoginController &controller;

        Gtk::Button *button;
    };
}


#endif //ELABORATO_ING_SW_LOGINVIEW_HPP
