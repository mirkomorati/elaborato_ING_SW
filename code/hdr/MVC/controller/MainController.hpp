//
// Created by Mirko Morati on 30/06/17.
//

#ifndef ELABORATO_ING_SW_MAINCONTROLLER_HPP
#define ELABORATO_ING_SW_MAINCONTROLLER_HPP

#include "../view/MainView.hpp"
#include "../model/MainModel.hpp"
#include <thread>

namespace mm {
    class MainView;

    class MainModel;

    class MainController {
    public:
        MainController();

        MainController(MainView *window, MainModel *model);

        ~MainController();

        void setWindow(MainView *window);

        void setModel(MainModel *model);

        void login(std::string name, std::string password);

        void login(int id);

    private:
        MainView *view;
        MainModel *model;
    };
}

#endif //ELABORATO_ING_SW_MAINCONTROLLER_HPP
