//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_MAINVIEW_HPP
#define ELABORATO_ING_SW_MAINVIEW_HPP

#include <gtkmm-3.0/gtkmm.h>
#include "../controller/Main.hpp"
#include "Patient.hpp"
#include "Login.hpp"

namespace mm {
    namespace controller {
        class Main;
    }

    namespace view {
        class Patient;

        class Login;

        enum StackPage {
            LOGIN,
            PATIENT
        };

        class Main {
        public:
            Main(controller::Main &controller);

            ~Main();

            Gtk::ApplicationWindow &get_app_window();

            view::Login &get_login_view();

            view::Patient &get_patient_view();

            void setup();

            void change_stack_page(StackPage page);

        private:
            view::Login *login_view;
            Patient *patient_view;

            controller::Main &controller;

            Gtk::ApplicationWindow *window;
            Gtk::MenuItem *logout_menu;
        };
    }
}

#endif //ELABORATO_ING_SW_MAINVIEW_HPP
