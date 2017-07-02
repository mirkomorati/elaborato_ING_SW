//
// Created by Noè Murr on 02/07/2017.
//

#ifndef ELABORATO_ING_SW_LOGINVIEW_HPP
#define ELABORATO_ING_SW_LOGINVIEW_HPP

#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include <gtkmm/label.h>
#include "../controller/LoginController.hpp"
#include "../controller/MainController.hpp"

namespace mm {
    class LoginView {
    private:
        // graphic elements
        Gtk::Button *login_button;
        Gtk::Entry *login_name, *login_pswd;
        Gtk::Label *login_error;

        // logic
        LoginController *controller;
        MainView *parent;

    public:

        LoginView(mm::MainView *parent, LoginController *controller, Glib::RefPtr<Gtk::Builder> refBuilder);

        void onLoginButtonClicked();

        void loginFailed();
    };
}


#endif //ELABORATO_ING_SW_LOGINVIEW_HPP
