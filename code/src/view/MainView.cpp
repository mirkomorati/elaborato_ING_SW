//
// Created by Noè Murr on 03/07/2017.
//

#include <gtkmm/builder.h>
#include <iostream>
#include "../../hdr/view/MainView.hpp"
#include "../../hdr/RefBuilder.hpp"

mm::MainView::MainView(mm::MainController &controller)
        : controller(controller) {
    login_view = new LoginView(&controller.get_login_controller());
    patient_view = new PatientView(&controller.get_patient_controller());

    auto &refBuilder = RefBuilder::get_instance();
    refBuilder.get_widget("mainWindow", window);
    //refBuilder.get_widget("logoutButton", logout_menu);

    //logout_menu->signal_activate().connect(sigc::mem_fun(controller, &mm::MainController::on_button_logout_clicked));
}

Gtk::ApplicationWindow &mm::MainView::get_app_window() {
    return *window;
}

mm::LoginView &mm::MainView::get_login_view() {
    return *login_view;
}

mm::PatientView &mm::MainView::get_patient_view() {
    return *patient_view;
}

mm::MainView::~MainView() {
    delete login_view;
    delete patient_view;
}

void mm::MainView::setup() {
    login_view->set_parent(this);
}

void mm::MainView::change_stack_page(mm::StackPage page) {
    auto &refBuilder = RefBuilder::get_instance();
    Gtk::Stack *stack;
    Gtk::MenuBar *menu_bar;

    refBuilder.get_widget("mainStack", stack);
    refBuilder.get_widget("menuBar", menu_bar);

    switch (page) {
        case LOGIN:
            menu_bar->set_visible(false);
            stack->set_visible_child("loginGrid");
            cout << "login page" << endl;
            break;
        case PATIENT:
            menu_bar->set_visible(true);
            stack->set_visible_child("patientPaned");
            break;
    }
}


