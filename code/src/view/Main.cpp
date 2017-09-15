//
// Created by Noè Murr on 03/07/2017.
//

#include <gtkmm/builder.h>
#include <iostream>
#include "../../hdr/view/Main.hpp"
#include "../../hdr/RefBuilder.hpp"
#include "../../hdr/controller/Register.hpp"

mm::view::Main::Main()
        : controller(controller::Register::get_instance().getMain_controller()) {
    login_view = new Login();
    patient_view = new Patient();

    auto &refBuilder = RefBuilder::get_instance();
    refBuilder.get_widget("mainWindow", window);
    refBuilder.get_widget("quitMenu", logout_menu);

    logout_menu->signal_activate().connect(sigc::mem_fun(controller, &mm::controller::Main::on_button_logout_clicked));
    window->signal_key_press_event().connect(sigc::mem_fun(controller, &mm::controller::Main::key_pressed_handler),
                                             false);
}

Gtk::ApplicationWindow &mm::view::Main::get_app_window() {
    return *window;
}

mm::view::Login &mm::view::Main::get_login_view() {
    return *login_view;
}

mm::view::Patient &mm::view::Main::get_patient_view() {
    return *patient_view;
}

mm::view::Main::~Main() {
    delete login_view;
    delete patient_view;
}

void mm::view::Main::setup() {
    login_view->set_parent(this);
}

void mm::view::Main::change_stack_page(mm::view::StackPage page) {
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
            controller.set_actual_page(mm::controller::StackPage::LOGIN);
            break;
        case PATIENT:
            menu_bar->set_visible(true);
            stack->set_visible_child("patientPaned");
            controller.set_actual_page(mm::controller::StackPage::PATIENT);
            break;
    }
}


