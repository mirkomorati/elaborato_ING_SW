//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_LOGINCONTROLLER_HPP
#define ELABORATO_ING_SW_LOGINCONTROLLER_HPP

#include "../view/LoginView.hpp"

namespace mm {
    class LoginView;

    class MainController;

    class LoginController {
    public:
        LoginController();

        void set_view(LoginView *view);

        void login_button_handler();

        void set_parent(MainController *parent);

    private:
        LoginView *login_view;
        MainController *parent;
    };
}

#endif //ELABORATO_ING_SW_LOGINCONTROLLER_HPP
