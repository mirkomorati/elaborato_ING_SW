//
// Created by Noè Murr on 03/07/2017.
//

#include <iostream>
#include <thread>
#include "../../hdr/controller/LoginController.hpp"
#include "../../hdr/RefBuilder.hpp"
#include "../../hdr/model/LoginModel.hpp"


void mm::LoginController::set_view(LoginView *view) {
    login_view = view;
}

void mm::LoginController::login_button_handler() {
    auto &refBuilder = RefBuilder::get_instance();

    Gtk::Entry *name;
    Gtk::Entry *password;

    refBuilder.get_widget("loginName", name);
    refBuilder.get_widget("loginPassword", password);
    std::string text_name = name->get_text();
    std::string text_password = password->get_text();
    std::cout << "Nome: " << text_name << "\tPassword: "
              << text_password << std::endl;

    std::thread login_thread([this](std::string name, std::string password) {
        auto login_data = LoginModel().get_login_data();
        for (auto login : login_data) {
            if (std::get<0>(login) == name && std::get<1>(login) == password) {
                login_view->login_update(true);
                parent->set_doctor(get<2>(login));
                return 0;
            }
        }
        login_view->login_update(false);
        return -1;
    }, text_name, text_password);

    login_thread.detach();
}

mm::LoginController::LoginController() {
}

void mm::LoginController::set_parent(mm::MainController *parent) {
    LoginController::parent = parent;
}
