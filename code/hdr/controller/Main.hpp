//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_MAINCONTROLLER_HPP
#define ELABORATO_ING_SW_MAINCONTROLLER_HPP


#include "Login.hpp"
#include "Patient.hpp"
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

        class Patient;

        class Main {
        public:
            Main();

            virtual ~Main();

            controller::Login &get_login_controller();

            Patient &get_patient_controller();

            Gtk::ApplicationWindow &get_main_window();

            void set_doctor(int doctor_id);

            void setup();

            void on_button_logout_clicked();

            StackPage get_actual_page() const;

            void set_actual_page(StackPage actual_page);

            bool key_pressed_handler(GdkEventKey *event);

        private:
            controller::Login *login_controller;
            controller::Patient *patient_controller;
            view::Main *main_view;
            StackPage actual_page;
        };
    }
}


#endif //ELABORATO_ING_SW_MAINCONTROLLER_HPP
