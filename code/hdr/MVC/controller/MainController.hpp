//
// Created by Mirko Morati on 30/06/17.
//

#ifndef ELABORATO_ING_SW_MAINCONTROLLER_HPP
#define ELABORATO_ING_SW_MAINCONTROLLER_HPP

#include "../view/MainWindow.hpp"
#include "../model/MainModel.hpp"

namespace mm {
  class MainWindow;

  class MainController {
  public:
    MainController();

    MainController(MainWindow *window, MainModel *model);

    ~MainController();

    void setWindow(MainWindow *window);

    void setModel(MainModel *model);

    bool login(std::string name, std::string password);

  private:
    MainWindow *window;
    MainModel *model;
  };
}

#endif //ELABORATO_ING_SW_MAINCONTROLLER_HPP
