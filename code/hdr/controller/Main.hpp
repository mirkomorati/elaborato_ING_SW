//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_MAINCONTROLLER_HPP
#define ELABORATO_ING_SW_MAINCONTROLLER_HPP


#include "Login.hpp"
#include "Patient.hpp"
#include "../view/Main.hpp"

namespace mm {
    namespace view {
        class Main;
    }

    namespace controller {
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

        private:
            controller::Login *login_controller;
            controller::Patient *patient_controller;
            view::Main *main_view;
        };
    }
}


#endif //ELABORATO_ING_SW_MAINCONTROLLER_HPP
