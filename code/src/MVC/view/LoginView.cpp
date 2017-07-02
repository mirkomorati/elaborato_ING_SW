//
// Created by Noè Murr on 02/07/2017.
//

#include <gtkmm/entry.h>
#include "../../../hdr/MVC/view/LoginView.hpp"

void mm::LoginView::onLoginButtonClicked() {
    controller->login(login_name->get_text(),
                      login_pswd->get_text());
}

mm::LoginView::LoginView(mm::MainView *parent, mm::LoginController *controller, Glib::RefPtr<Gtk::Builder> refBuilder)
        : controller(controller), parent(parent) {

    // ottengo le informazioni di cui ho bisogno.
    refBuilder->get_widget("loginButton", login_button);
    refBuilder->get_widget("loginName", login_name);
    refBuilder->get_widget("loginPassword", login_pswd);
    refBuilder->get_widget("loginError", login_error);

    login_button->signal_clicked().connect(
            sigc::mem_fun(*this, &LoginView::onLoginButtonClicked));
}

void mm::LoginView::loginFailed() {
    login_error->set_visible(true);
}

