//
// Created by Noè Murr on 03/07/2017.
//

#include <iostream>
#include "../../hdr/view/LoginView.hpp"
#include "../../hdr/RefBuilder.hpp"

mm::LoginView::LoginView(LoginController *controller) : controller(controller) {
    auto &refBuilder = RefBuilder::get_instance();

    refBuilder.get_widget("loginButton", button);

    button->signal_clicked().connect(sigc::mem_fun(
        controller, &mm::LoginController::login_button_handler));
}

void mm::LoginView::login_update(bool success) {
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

void mm::LoginView::set_parent(mm::MainView *parent) {
    this->parent = parent;
}
