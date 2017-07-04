//
// Created by Noè Murr on 03/07/2017.
//

#include <gtkmm/builder.h>
#include "../../hdr/view/MainView.hpp"
#include "../../hdr/RefBuilder.hpp"

mm::MainView::MainView(mm::MainController &controller)
        : controller(controller), login_view(controller.get_login_controller()),
          patient_view(controller.get_patient_controller()) {

    auto &refBuilder = RefBuilder::get_instance();
    refBuilder.get_widget("mainWindow", window);
}

Gtk::ApplicationWindow &mm::MainView::get_app_window() {
    return *window;
}

mm::LoginView &mm::MainView::get_login_view() {
    return login_view;
}

mm::PatientView &mm::MainView::get_patient_view() {
    return patient_view;
}


