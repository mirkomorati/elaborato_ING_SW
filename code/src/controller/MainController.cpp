//
// Created by Noè Murr on 03/07/2017.
//

#include "../../hdr/controller/MainController.hpp"

mm::MainController::MainController() {
    main_view = new MainView(*this);
    login_controller.set_view(main_view->get_login_view());
    patient_controller.set_view(main_view->get_patient_view());
}

Gtk::ApplicationWindow &mm::MainController::get_main_window() {
    return main_view->get_app_window();
}

mm::LoginController &mm::MainController::get_login_controller() {
    return login_controller;
}

mm::PatientController &mm::MainController::get_patient_controller() {
    return patient_controller;
}

mm::MainController::~MainController() {
    delete main_view;
}
