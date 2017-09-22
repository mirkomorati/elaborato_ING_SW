//
// Created by Noè Murr on 03/07/2017.
//

#include <gtkmm/builder.h>
#include <iostream>
#include "../../hdr/view/Main.hpp"
#include "../../hdr/RefBuilder.hpp"
#include "../../hdr/controller/Register.hpp"

mm::view::Main::Main()
        : controller(controller::Register::get_instance().get_main()) {
    login_view = new Login();
    patient_view = new Application(controller::Register::get_instance().get_patient());

    auto &refBuilder = RefBuilder::get_instance();
    refBuilder.get_widget("mainWindow", window);
    refBuilder.get_widget("quitMenu", logout_menu);

    logout_menu->signal_activate().connect(sigc::mem_fun(
            controller, &mm::controller::Main::on_button_logout_clicked));
    window->signal_key_press_event().connect(sigc::mem_fun(
            controller, &mm::controller::Main::key_pressed_handler), false);
}

Gtk::ApplicationWindow &mm::view::Main::get_app_window() {
    return *window;
}

mm::view::Login &mm::view::Main::get_login_view() {
    return *login_view;
}

mm::view::Application &mm::view::Main::get_patient_view() {
    return *patient_view;
}

mm::view::Main::~Main() {
    delete login_view;
    delete patient_view;
}

void mm::view::Main::setup() {
    login_view->set_parent(this);
    auto css_provider = Gtk::CssProvider::create();
    // todo spostare il file in un posto migliore (cartella delle resources..?)
    try {
        css_provider->load_from_path("../../../../glade/style.css");
    } catch (Gtk::CssProviderError &ex) {
        cout << "CssProviderError: " << ex.what();
    }
    Gtk::StyleContext::add_provider_for_screen(Gdk::Screen::get_default(), css_provider,
                                               800);  // 800 = Gtk::STYLE_PROVIDER_PRIORITY_USER che non trovo
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
        case APPLICATION:
            menu_bar->set_visible(true);
            stack->set_visible_child("patientPaned");
            controller.set_actual_page(mm::controller::StackPage::APPLICATION);
            break;
    }
}


