//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_MAINCONTROLLER_HPP
#define ELABORATO_ING_SW_MAINCONTROLLER_HPP


#include "Login.hpp"
#include "Application.hpp"
#include "../view/Main.hpp"
#include <gdk/gdk.h>

namespace mm {
    namespace view {
        class Main;
    }

    namespace controller {

        enum StackPage {
            LOGIN,
            PATIENT
        };

        class Login;

        class Application;

        class Main {
        public:
            Main() = default;

            virtual ~Main();

            Gtk::ApplicationWindow &get_main_window();

            void set_doctor(int doctor_id);

            void setup();

            void on_button_logout_clicked();

            StackPage get_actual_page() const;

            void set_actual_page(StackPage actual_page);

            bool key_pressed_handler(GdkEventKey *event);

        private:
            view::Main *main_view;
            StackPage actual_page;
        };
    }
}


#endif //ELABORATO_ING_SW_MAINCONTROLLER_HPP
