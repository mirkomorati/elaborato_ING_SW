//
// Created by Noè Murr on 03/07/2017.
//

#include <iostream>
#include <thread>
#include "../../hdr/controller/Login.hpp"
#include "../../hdr/RefBuilder.hpp"
#include "../../hdr/model/Authentication.hpp"


void mm::controller::Login::set_view(view::Login *view) {
    this->view = view;
}

void mm::controller::Login::login_button_handler() {
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
        auto login_data = mm::model::Authentication().get_login_data();
        for (auto login : login_data) {
            if (std::get<0>(login) == name && std::get<1>(login) == password) {
                view->login_update(true);
                parent->set_doctor(get<2>(login));
                return 0;
            }
        }
        view->login_update(false);
        return -1;
    }, text_name, text_password);

    login_thread.detach();
}

void mm::controller::Login::set_parent(mm::controller::Main *parent) {
    this->parent = parent;
}

bool mm::controller::Login::key_pressed_handler(GdkEventKey *event) {
    if (event->keyval == GDK_KEY_Return) {
        login_button_handler();
        return true;
    }
    return false;
}
