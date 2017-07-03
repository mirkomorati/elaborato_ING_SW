//
// Created by Mirko Morati on 30/06/17.
//

#include "../../../../code/hdr/MVC/controller/MainController.hpp"
#include <iostream>

mm::MainController::MainController(mm::MainView *window, mm::MainModel *model)
        : view(window), model(model) {
}

mm::MainController::~MainController() {

}

void mm::MainController::login(std::string name, std::string password) {
    std::cout << "Nome: " << name << "\tPassword: " << password << std::endl;

    std::thread login_thread([this](std::string name, std::string password) {
        auto login_data = model->get_login_data();
        for (auto login : login_data) {
            if (std::get<0>(login) == name && std::get<1>(login) == password) {
                view->login_update(std::get<2>(login));
                return 0;
            }
        }
        view->login_update(-1);
        return -1;
    }, name, password);

    login_thread.detach();
}

mm::MainController::MainController() {

}

void mm::MainController::setWindow(mm::MainView *window) {
    MainController::view = window;
}

void mm::MainController::setModel(mm::MainModel *model) {
    MainController::model = model;
}

mm::MainController::MainController() {

}

mm::MainController::MainController() {

}
