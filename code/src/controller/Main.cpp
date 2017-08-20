//
// Created by Noè Murr on 03/07/2017.
//

#include "../../hdr/controller/Main.hpp"

mm::controller::Main::Main() {
    login_controller = new Login();
    patient_controller = new Patient();
}

Gtk::ApplicationWindow &mm::controller::Main::get_main_window() {
    return main_view->get_app_window();
}

mm::controller::Login &mm::controller::Main::get_login_controller() {
    return *login_controller;
}

mm::controller::Patient &mm::controller::Main::get_patient_controller() {
    return *patient_controller;
}

mm::controller::Main::~Main() {
    delete main_view;
    delete patient_controller;
    delete login_controller;
}

void mm::controller::Main::setup() {
    main_view = new view::Main(*this);
    login_controller->set_view(&main_view->get_login_view());
    login_controller->set_parent(this);
    patient_controller->set_view(&main_view->get_patient_view());
    patient_controller->set_parent(this);
    main_view->setup();
}

void mm::controller::Main::set_doctor(int doctor_id) {
    patient_controller->set_doctor(doctor_id);
}

void mm::controller::Main::on_button_logout_clicked() {
    main_view->change_stack_page(view::LOGIN);
    patient_controller->set_doctor(-1);
}

mm::controller::StackPage mm::controller::Main::get_actual_page() const {
    return actual_page;
}

void mm::controller::Main::set_actual_page(mm::controller::StackPage actual_page) {
    Main::actual_page = actual_page;
}

bool mm::controller::Main::key_pressed_handler(GdkEventKey *event) {
    if (actual_page == LOGIN) {
        if (event->keyval == GDK_KEY_Return) {
            login_controller->login_button_handler();
            return true;
        }
    }
    return false;
}
