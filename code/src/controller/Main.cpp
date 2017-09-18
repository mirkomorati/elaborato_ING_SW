//
// Created by Noè Murr on 03/07/2017.
//

#include <iostream>
#include "../../hdr/controller/Main.hpp"
#include "../../hdr/controller/Register.hpp"


Gtk::ApplicationWindow &mm::controller::Main::get_main_window() {
    return main_view->get_app_window();
}

mm::controller::Main::~Main() {
    delete main_view;
}

void mm::controller::Main::setup() {
    main_view = new view::Main();
    Register::get_instance().get_login().set_view(&main_view->get_login_view());
    Register::get_instance().get_patient().set_view(&main_view->get_patient_view());
    main_view->setup();
}

void mm::controller::Main::set_doctor(int doctor_id) {
    Register::get_instance().get_patient().set_doctor(doctor_id);
}

void mm::controller::Main::on_button_logout_clicked() {
    main_view->change_stack_page(view::LOGIN);
    Register::get_instance().get_patient().set_doctor(-1);
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
            Register::get_instance().get_login().login_button_handler();
            return true;
        }
    } else if (actual_page == PATIENT) {
        if (event->keyval == GDK_KEY_Escape) {
            Register::get_instance().get_patient().unselect_patient();
        }
    }
    return false;
}
