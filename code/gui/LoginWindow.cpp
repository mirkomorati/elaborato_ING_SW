//
// Created by Noè Murr on 29/11/2017.
//

#include <gtkmm/entry.h>
#include <spdlog/spdlog.h>
#include "LoginWindow.hpp"
#include "../RefBuilder.hpp"
#include "../model/Authentication.hpp"

bool mm::LoginWindow::init() {
    Gtk::Button *button;
    RefBuilder::get_instance().get_widget("loginButton", button);
    button->signal_clicked().connect(sigc::mem_fun(this, &mm::LoginWindow::onLoginButtonClicked));
    return true;
}

mm::WindowName mm::LoginWindow::getName() const {
    return LOGIN;
}

mm::WindowName mm::LoginWindow::getNextWindow() const {
    return next;
}

mm::LoginWindow::LoginWindow() : next(LOGIN) {}

void mm::LoginWindow::onLoginButtonClicked() {
    auto &refBuilder = RefBuilder::get_instance();
    auto log = spdlog::get("out");

    Gtk::Entry *name;
    Gtk::Entry *password;

    refBuilder.get_widget("loginName", name);
    refBuilder.get_widget("loginPassword", password);
    log->debug("try to log in with username: {} and password: {}", static_cast<std::string>(name->get_text()),
               static_cast<std::string>(password->get_text()));

    if (model::authentication::check_login(name->get_text(), password->get_text())) {
        log->info("log in with user: {}", static_cast<std::string>(name->get_text()));
        next = MAIN;
        notify();
    } else {
        log->info("failed authentication");
        Gtk::Label *error;
        refBuilder.get_widget("loginError", error);
        error->set_visible(true);
    }
}
