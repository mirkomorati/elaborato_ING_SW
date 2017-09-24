//
// Created by Noè Murr on 03/07/2017.
//

#include <gtkmm/builder.h>
#include <iostream>
#include "../../hdr/view/Main.hpp"
#include "../../hdr/RefBuilder.hpp"
#include "../../hdr/controller/Register.hpp"

/*mm::view::Main::Main(controller::Main &c)
        : controller(controller::Register::get_instance().get_main()) {
    login_view = new Login();
    patient_view = new Application(controller::Register::get_instance().get_patient_from_health_code());

    Gtk::ImageMenuItem *about;
    Gtk::AboutDialog *about_dialog;
    auto &refBuilder = RefBuilder::get_instance();
    refBuilder.get_widget("mainWindow", window);
    refBuilder.get_widget("quitMenu", logout_menu);
    refBuilder.get_widget("aboutMenuItem", about);
    refBuilder.get_widget("aboutDialog", about_dialog);

    logout_menu->signal_activate().connect(sigc::mem_fun(controller, &mm::controller::Main::on_button_logout_clicked));
    window->signal_key_press_event().connect(sigc::mem_fun(controller, &mm::controller::Main::key_pressed_handler),
                                             false);
    about->signal_activate().connect(sigc::mem_fun(controller, &mm::controller::Main::about_dialog_handler));
    about_dialog->signal_response().connect(sigc::mem_fun(controller, &mm::controller::Main::about_dialog_response));
    about_dialog->signal_activate_link().connect(sigc::mem_fun(controller, &mm::controller::Main::about_dialog_link),
                                                 false);
}*/

/*mm::view::Login &mm::view::Main::get_login_view() {
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
}

}*/

mm::view::Main::Main(controller::Main &c) : model(c.get_model()) {
    Gtk::ImageMenuItem *about;
    Gtk::AboutDialog *about_dialog;
    //Gtk::MenuItem *logout_menu;
    auto &refBuilder = RefBuilder::get_instance();
    refBuilder.get_widget("mainWindow", window);
    //refBuilder.get_widget("quitMenu", logout_menu);
    refBuilder.get_widget("aboutMenuItem", about);
    refBuilder.get_widget("aboutDialog", about_dialog);

    //logout_menu->signal_activate().connect(sigc::mem_fun(&c, &mm::controller::Main::on_button_logout_clicked));
    window->signal_key_press_event().connect(sigc::mem_fun(&c, &mm::controller::Main::key_pressed_handler), false);
    about->signal_activate().connect(sigc::mem_fun(&c, &mm::controller::Main::about_dialog_handler));
    about_dialog->signal_response().connect(sigc::mem_fun(&c, &mm::controller::Main::about_dialog_response));
    about_dialog->signal_activate_link().connect(sigc::mem_fun(&c, &mm::controller::Main::about_dialog_link), false);

    auto css_provider = Gtk::CssProvider::create();
    // todo spostare il file in un posto migliore (cartella delle resources..?)
    try {
        css_provider->load_from_path("../../../../glade/style.css");
    } catch (Gtk::CssProviderError &ex) {
        std::cout << "CssProviderError: " << ex.what() << std::endl;
    }
    Gtk::StyleContext::add_provider_for_screen(Gdk::Screen::get_default(), css_provider,
                                               800);  // 800 = Gtk::STYLE_PROVIDER_PRIORITY_USER che non trovo

    c.attach(this);
}

Gtk::ApplicationWindow &mm::view::Main::get_app_window() {
    return *window;
}

void mm::view::Main::change_stack_page() {
    auto page = model->stackPage.first;
    auto &refBuilder = RefBuilder::get_instance();
    Gtk::Stack *stack;
    Gtk::MenuBar *menu_bar;

    refBuilder.get_widget("mainStack", stack);
    refBuilder.get_widget("menuBar", menu_bar);

    switch (page) {
        case model::LOGIN:
            menu_bar->set_visible(false);
            stack->set_visible_child("loginGrid");
            cout << "login page" << endl;
            break;
        case model::APPLICATION:
            menu_bar->set_visible(true);
            stack->set_visible_child("patientPaned");
            Gtk::StyleContext::remove_provider_for_screen(Gdk::Screen::get_default(), Gtk::CssProvider::get_default());
            break;
    }
}

void mm::view::Main::update() {

    if (model->stackPage.second) {
        change_stack_page();
        model->stackPage.second = false;
    }

}

