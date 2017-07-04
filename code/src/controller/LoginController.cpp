//
// Created by Noè Murr on 03/07/2017.
//

#include <iostream>
#include <thread>
#include "../../hdr/controller/LoginController.hpp"
#include "../../hdr/RefBuilder.hpp"
#include "../../hdr/LoginModel.hpp"


void mm::LoginController::set_view(LoginView *view) {
    login_view = view;
}

void mm::LoginController::login_button_handler() {
    auto &refBuilder = RefBuilder::get_instance();

    Gtk::Entry *name;
    Gtk::Entry *password;

    refBuilder.get_widget("loginName", name);
    refBuilder.get_widget("loginPassword", password);

    std::cout << "Nome: " << name->get_text() << "\tPassword: "
              << password->get_text() << std::endl;

    std::thread login_thread([this](std::string name, std::string password) {
        LoginModel model;
        auto login_data = model.get_login_data();
        for (auto login : login_data) {
            if (std::get<0>(login) == name && std::get<1>(login) == password) {
                login_view->login_update(std::get<2>(login));
                return 0;
            }
        }
        login_view->login_update(-1);
        return -1;
    }, name->get_text(), password->get_text());

    login_thread.detach();
}

mm::LoginController::LoginController() {
}
