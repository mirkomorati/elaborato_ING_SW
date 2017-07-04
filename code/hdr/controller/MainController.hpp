//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_MAINCONTROLLER_HPP
#define ELABORATO_ING_SW_MAINCONTROLLER_HPP


#include "LoginController.hpp"
#include "PatientController.hpp"
#include "../view/MainView.hpp"

namespace mm {
    class MainView;

    class LoginController;

    class PatientController;

    class MainController {
    public:
        MainController();

        virtual ~MainController();

        LoginController &get_login_controller();

        PatientController &get_patient_controller();

        Gtk::ApplicationWindow &get_main_window();

        void set_doctor(int doctor_id);

        void setup();

    private:
        LoginController *login_controller;
        PatientController *patient_controller;
        MainView *main_view;
    };
}


#endif //ELABORATO_ING_SW_MAINCONTROLLER_HPP
