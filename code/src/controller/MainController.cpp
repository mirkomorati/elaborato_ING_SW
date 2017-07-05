//
// Created by Noè Murr on 03/07/2017.
//

#include "../../hdr/controller/MainController.hpp"

mm::MainController::MainController() {
    login_controller = new LoginController();
    patient_controller = new PatientController();
}

Gtk::ApplicationWindow &mm::MainController::get_main_window() {
    return main_view->get_app_window();
}

mm::LoginController &mm::MainController::get_login_controller() {
    return *login_controller;
}

mm::PatientController &mm::MainController::get_patient_controller() {
    return *patient_controller;
}

mm::MainController::~MainController() {
    delete main_view;
    delete patient_controller;
    delete login_controller;
}

void mm::MainController::setup() {
    main_view = new MainView(*this);
    login_controller->set_view(&main_view->get_login_view());
    login_controller->set_parent(this);
    patient_controller->set_view(&main_view->get_patient_view());
    patient_controller->set_parent(this);
    main_view->setup();
}

void mm::MainController::set_doctor(int doctor_id) {
    patient_controller->set_doctor(doctor_id);
}

void mm::MainController::on_button_logout_clicked() {
    main_view->change_stack_page(LOGIN);
}
