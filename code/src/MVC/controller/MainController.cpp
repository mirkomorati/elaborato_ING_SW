//
// Created by Mirko Morati on 30/06/17.
//

#include "../../../hdr/MVC/controller/MainController.hpp"
#include <iostream>

mm::MainController::MainController(mm::MainWindow *window, mm::MainModel *model) : window(window), model(model) {
}

mm::MainController::~MainController() {

}

bool mm::MainController::login(std::string name, std::string password) {
  std::cout << "Nome: " << name << "\tPassword: " << password << std::endl;
  return true;
}

mm::MainController::MainController() {

}

void mm::MainController::setWindow(mm::MainWindow *window) {
  MainController::window = window;
}

void mm::MainController::setModel(mm::MainModel *model) {
  MainController::model = model;
}
