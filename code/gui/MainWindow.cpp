//
// Created by Noè Murr on 29/11/2017.
//

#include "MainWindow.hpp"

bool mm::MainWindow::init() {
    return false;
}

mm::WindowName mm::MainWindow::getName() const {
    return MAIN;
}

mm::WindowName mm::MainWindow::getNextWindow() const {
    return next;
}

mm::MainWindow::MainWindow() : next(MAIN) {}
