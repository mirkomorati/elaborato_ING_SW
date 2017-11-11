
//
// Created by Noè Murr on 03/07/2017.
//

#include <iostream>
#include <spdlog/spdlog.h>
#include "../../hdr/controller/Main.hpp"
#include "../../hdr/controller/Register.hpp"
#include "../../hdr/model/Authentication.hpp"

mm::controller::Main::Main() : model(new model::Main) {}

void mm::controller::Main::about_dialog_response(int response_id) {
    Gtk::AboutDialog *about_dialog;
    RefBuilder::get_instance().get_widget("aboutDialog", about_dialog);
    about_dialog->hide();
}

void mm::controller::Main::about_dialog_handler() {
    Gtk::AboutDialog *about_dialog;
    RefBuilder::get_instance().get_widget("aboutDialog", about_dialog);
    about_dialog->show();
}

bool mm::controller::Main::about_dialog_link(const Glib::ustring &uri) {
    std::system(Glib::ustring("open ").append(uri).c_str());
    // todo no!! no! e poi NO.
}

bool mm::controller::Main::key_pressed_handler(GdkEventKey *event) {
    if (model->stackPage.first == model::LOGIN) {
        if (event->keyval == GDK_KEY_Return) {
            login_button_handler();
            return true;
        }
    } else if (model->stackPage.first == model::APPLICATION) {
        if (event->keyval == GDK_KEY_Escape) {
            Register::get_instance().get_patient().unselect_patient();
        }
    }
    notify();
    return false;
}

const shared_ptr<mm::model::Main> &mm::controller::Main::get_model() const {
    return model;
}

void mm::controller::Main::login_button_handler() {
    auto &refBuilder = RefBuilder::get_instance();
    auto log = spdlog::get("out");

    Gtk::Entry *name;
    Gtk::Entry *password;

    refBuilder.get_widget("loginName", name);
    refBuilder.get_widget("loginPassword", password);
    log->debug("try to log in with username: {} and password: {}", static_cast<std::string>(name->get_text()),
               static_cast<std::string>(password->get_text()));

    if (model::authentication::check_login(name->get_text(), password->get_text())) {
        model->stackPage.first = model::APPLICATION;
        model->stackPage.second = true;
        notify(); // cambio la pagina
        model::authentication::Login::get_instance().notify(); // avviso tutti che è cambiato il login
        // informare la application view
    } else {
        model->login_failed.first = model->login_failed.second = true;
        notify();
    }
}
