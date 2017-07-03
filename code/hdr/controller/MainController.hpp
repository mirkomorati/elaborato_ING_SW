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

    class MainController {
    public:
        MainController();

        void run();

        const LoginController &get_login_controller() const;

        const PatientController &get_patient_controller() const;

    private:
        LoginController login_controller;
        PatientController patient_controller;

        MainView main_view;
    };
}


#endif //ELABORATO_ING_SW_MAINCONTROLLER_HPP
