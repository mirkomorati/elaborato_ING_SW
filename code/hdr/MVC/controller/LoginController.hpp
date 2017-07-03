//
// Created by Noè Murr on 02/07/2017.
//

#ifndef ELABORATO_ING_SW_LOGINCONTROLLER_HPP
#define ELABORATO_ING_SW_LOGINCONTROLLER_HPP


#include <string>
#include "../model/LoginModel.hpp"
#include "MainController.hpp"
#include "../view/LoginView.hpp"

namespace mm {
    class LoginView;

    class MainController;

    class LoginController {
    private:
        LoginModel *model;
        LoginView *view;
        MainController *parent;

        std::mutex &delete_mutex;

    public:
        void login(std::string name, std::string pswd);

        LoginController(LoginModel *model, LoginView *view, MainController *parent, std::mutex &delete_mutex);
    };
}

#endif //ELABORATO_ING_SW_LOGINCONTROLLER_HPP
