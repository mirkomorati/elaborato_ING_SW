//
// Created by Noè Murr on 03/07/2017.
//

#include <iostream>
#include "../../hdr/view/Login.hpp"
#include "../../hdr/RefBuilder.hpp"

mm::view::Login::Login(controller::Login *controller) : controller(controller) {
    auto &refBuilder = RefBuilder::get_instance();

    refBuilder.get_widget("loginButton", button);

    button->signal_clicked().connect(sigc::mem_fun(
            controller, &mm::controller::Login::login_button_handler));

}

void mm::view::Login::login_update(bool success) {
    if (success) {
        std::cout << "Login eseguito" << std::endl;
        parent->change_stack_page(PATIENT);
    } else {
        Gtk::Label *login_error;

        std::cout << "Login fallito" << std::endl;
        RefBuilder::get_instance().get_widget("loginError", login_error);
        login_error->set_visible(true);
    }
}

void mm::view::Login::set_parent(mm::view::Main *parent) {
    this->parent = parent;
}
