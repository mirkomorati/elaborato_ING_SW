//
// Created by Noè Murr on 23/12/2017.
//

#include "MainWindow.hpp"
#include "RefBuilder.hpp"
#include "AboutDialog.hpp"

bool mm::MainWindow::init() {
    Gtk::MenuBar *menuBar;
    RefBuilder::get_instance().get_widget("menuBar", menuBar);
    menuBar->set_visible(true);

    initHandlers();

    return true;
}

mm::WindowName mm::MainWindow::getName() const {
    return MAIN;
}

mm::WindowName mm::MainWindow::getNextWindow() const {
    return next;
}

void mm::MainWindow::initHandlers() {
    auto refBuilder = RefBuilder::get_instance();
    Gtk::MenuItem *logoutMenuItem;
    Gtk::ImageMenuItem *aboutMenuItem;

    refBuilder.get_widget("logoutMenuItem", logoutMenuItem);
    refBuilder.get_widget("aboutMenuItem", aboutMenuItem);
    logoutMenuItem->signal_activate().connect(sigc::mem_fun(this, &mm::MainWindow::onLogout));
    aboutMenuItem->signal_activate().connect(sigc::mem_fun(this, &mm::MainWindow::onAboutClicked));
}

void mm::MainWindow::onLogout() {
    next = LOGIN;
    notify();
}

void mm::MainWindow::onAboutClicked() {
    std::unique_ptr<Dialog> dialog(new AboutDialog);
    dialog->show();
    dialog->attach(this);
    dialogList.push_back(std::move(dialog));
}

void mm::MainWindow::update() {
    for (auto it = dialogList.begin(); it != dialogList.end(); ++it)
        if (not(*it)->isActive()) dialogList.erase(it);
}

void mm::MainWindow::onPageSwitch(Gtk::Widget *page, guint page_number) {
    (void **) page; // for unused warning

    switch (page_number) {
        case 0: {
            break;
        }
        case 1: {
            break;
        }
        case 2: {
            break;
        }
        default:
            throw std::logic_error("switch on unknown page");
    }
}

