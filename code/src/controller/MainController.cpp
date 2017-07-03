//
// Created by Noè Murr on 03/07/2017.
//

#include "../../hdr/controller/MainController.hpp"

mm::MainController::MainController() {
    main_view = new MainView(*this);
    login_controller.set_view(main_view->get_login_view());
    patient_controller.set_view(main_view->get_patient_view());
}

void mm::MainController::run() {
    int argc = 0;
    char **argv = nullptr;
    auto app = Gtk::Application::create(argc, argv, "it.mm.org");

    app->run(main_view->get_app_window());
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
