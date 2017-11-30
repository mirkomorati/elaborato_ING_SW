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

void mm::MainWindow::update() {
    for (auto it = dialogList.begin(); it != dialogList.end(); ++it)
        if (not(*it)->isActive()) dialogList.erase(it);

    // todo reload models and updates views.
}
