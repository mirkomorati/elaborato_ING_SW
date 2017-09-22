//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_MAINVIEW_HPP
#define ELABORATO_ING_SW_MAINVIEW_HPP

#include <gtkmm-3.0/gtkmm.h>
#include "../controller/Main.hpp"
#include "Application.hpp"
#include "Login.hpp"
#include "../model/Main.hpp"

namespace mm {
    namespace controller {
        class Main;
    }

    namespace view {
        /*class Application;

        class Login;

        enum StackPage {
            LOGIN,
            APPLICATION
        };

        class Main {
        public:
            explicit Main();

            ~Main();

            Gtk::ApplicationWindow &get_app_window();

            view::Login &get_login_view(); // no

            view::Application &get_patient_view(); // no

            void setup(); // no

            void change_stack_page(StackPage page); // si

        private:
            view::Login *login_view;
            Application *patient_view;

            controller::Main &controller;

            Gtk::ApplicationWindow *window;
            Gtk::MenuItem *logout_menu;
        };*/

        class Main : public IObserver {
        public:
            Main(controller::Main &c);

            Gtk::ApplicationWindow &get_app_window();

            void change_stack_page();

            void update() override;

        private:
            shared_ptr<model::Main> model;
            Gtk::ApplicationWindow *window;
        };
    }
}

#endif //ELABORATO_ING_SW_MAINVIEW_HPP
