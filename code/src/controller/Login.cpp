//
// Created by Noè Murr on 03/07/2017.
//

#include <iostream>
#include <thread>
#include "../../hdr/controller/Login.hpp"
#include "../../hdr/RefBuilder.hpp"
#include "../../hdr/model/Authentication.hpp"
#include "../../hdr/controller/Register.hpp"
#include <plog/Log.h>


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
        model::authentication::Login account;
        if (model::authentication::check_login(name, password, account)) {
            view->login_update(true);
            Register::get_instance().get_main().set_doctor(account.regional_id);
            return 0;
        }

        view->login_update(false);
        return -1;

    }, text_name, text_password);

    login_thread.detach();
}

