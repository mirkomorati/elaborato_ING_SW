//
// Created by Noè Murr on 02/07/2017.
//

#include <iostream>
#include <thread>
#include "../../../hdr/MVC/controller/LoginController.hpp"

void mm::LoginController::login(std::string name, std::string pswd) {
    std::cout << "Nome: " << name << "\tPassword: " << pswd << std::endl;

    std::thread login_thread([this](std::string name, std::string password) {
        auto login_data = model->getLoginData();
        for (auto login : login_data) {
            if (std::get<0>(login) == name && std::get<1>(login) == password) {
                parent->login(std::get<2>(login));
                return 0;
            }
        }
        view->loginFailed();
        return -1;
    }, name, pswd);

    login_thread.detach();
}
