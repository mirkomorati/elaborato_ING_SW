//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_MAINVIEW_HPP
#define ELABORATO_ING_SW_MAINVIEW_HPP

#include <gtkmm-3.0/gtkmm.h>
#include "../controller/MainController.hpp"
#include "PatientView.hpp"
#include "LoginView.hpp"

namespace mm {
    class MainController;

    class LoginView;

    class PatientView;

    enum StackPage {
        LOGIN,
        PATIENT
    };

    class MainView {
    public:
        MainView(MainController &controller);

        ~MainView();

        Gtk::ApplicationWindow &get_app_window();

        LoginView &get_login_view();

        PatientView &get_patient_view();

        void setup();

        void change_stack_page(StackPage page);

    private:
        LoginView *login_view;
        PatientView *patient_view;

        MainController &controller;

        Gtk::ApplicationWindow *window;
        Gtk::MenuItem *logout_menu;
    };
}

#endif //ELABORATO_ING_SW_MAINVIEW_HPP