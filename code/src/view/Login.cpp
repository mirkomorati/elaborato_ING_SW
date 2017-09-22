//
// Created by Noè Murr on 03/07/2017.
//

#include <iostream>
#include "../../hdr/view/Login.hpp"
#include "../../hdr/RefBuilder.hpp"


mm::view::Login::Login(mm::controller::Main &c) : model(c.get_model()) {
    auto &refBuilder = RefBuilder::get_instance();
    Gtk::Button *button;

    refBuilder.get_widget("loginButton", button);

    button->signal_clicked().connect(sigc::mem_fun(&c, &mm::controller::Main::login_button_handler));

    c.attach(this);
}

void mm::view::Login::update() {
    if (model->login_failed.second and model->login_failed.first) {
        login_failed();
    }
}

void mm::view::Login::login_failed() {
    Gtk::Label *login_error;

    std::cout << "Login fallito" << std::endl;
    RefBuilder::get_instance().get_widget("loginError", login_error);
    login_error->set_visible(true);
}