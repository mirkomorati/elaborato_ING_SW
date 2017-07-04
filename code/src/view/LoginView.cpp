//
// Created by Noè Murr on 03/07/2017.
//

#include <iostream>
#include "../../hdr/view/LoginView.hpp"
#include "../../hdr/RefBuilder.hpp"

mm::LoginView::LoginView(LoginController &controller) : controller(controller) {
    auto &refBuilder = RefBuilder::get_instance();

    refBuilder.get_widget("loginButton", button);

    button->signal_clicked().connect(sigc::mem_fun(
        controller, &mm::LoginController::login_button_handler));
}

void mm::LoginView::login_update(int doctor_id) {
    if (doctor_id >= 0) {
        std::cout << "Login eseguito" << std::endl;
    } else {
        std::cout << "Login fallito" << std::endl;
    }
}
