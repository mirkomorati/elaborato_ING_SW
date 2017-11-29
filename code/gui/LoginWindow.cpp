//
// Created by Noè Murr on 29/11/2017.
//

#include "LoginWindow.hpp"

bool mm::LoginWindow::init() {
    return true;
}

mm::WindowName mm::LoginWindow::getName() const {
    return name;
}

mm::WindowName mm::LoginWindow::getNextWindow() const {
    return next;
}

mm::LoginWindow::LoginWindow() : name(LOGIN), next(name) {}
