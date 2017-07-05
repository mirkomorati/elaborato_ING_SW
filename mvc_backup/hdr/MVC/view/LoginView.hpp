//
// Created by Noè Murr on 02/07/2017.
//

#ifndef ELABORATO_ING_SW_LOGINVIEW_HPP
#define ELABORATO_ING_SW_LOGINVIEW_HPP

#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include <gtkmm/label.h>
#include "../controller/MainController.hpp"

namespace mm {
    class LoginController;

    class MainView;

    class LoginView {
    private:
        // graphic elements
        Gtk::Button *login_button;
        Gtk::Entry *login_name, *login_pswd;
        Gtk::Label *login_error;

        MainView *parent;
        std::mutex &delete_mutex;

    public:

        LoginView(mm::MainView *parent, Glib::RefPtr<Gtk::Builder> refBuilder,
                  std::mutex &mutex);

        void onLoginButtonClicked();

        void loginFailed();
    };
}


#endif //ELABORATO_ING_SW_LOGINVIEW_HPP
