//
// Created by Noè Murr on 23/12/2017.
//

#include <spdlog/spdlog.h>
#include "MainWindow.hpp"
#include "PrescriptionWindow.hpp"
#include "RefBuilder.hpp"
#include "AboutDialog.hpp"
#include "PatientWindow.hpp"
#include "DrugWindow.hpp"

bool mm::MainWindow::init() {
    Gtk::MenuBar *menuBar;
    RefBuilder::get_instance().get_widget("menuBar", menuBar);
    menuBar->set_visible(true);

    initHandlers();

    for (const auto &tab : tabWindows) tab->init();

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
    Gtk::Notebook *notebook;

    refBuilder.get_widget("logoutMenuItem", logoutMenuItem);
    refBuilder.get_widget("aboutMenuItem", aboutMenuItem);
    refBuilder.get_widget("mainNotebook", notebook);
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
    spdlog::get("out")->debug("MainWindow::dialogList size after push_back: {}", dialogList.size());
}

void mm::MainWindow::update() {
    auto it = dialogList.begin();
    while (it != dialogList.end()) {
        if (not(*it)->isActive())
            it = dialogList.erase(it);
        else
            ++it;
    }
    spdlog::get("out")->debug("MainWindow::dialogList size after erase: {}", dialogList.size());
}

mm::MainWindow::MainWindow() : next(MAIN),
                               tabWindows({std::make_unique<PatientWindow>(), std::make_unique<DrugWindow>()}) {}

