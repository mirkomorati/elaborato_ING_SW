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

    class LoginModel;
    class MainModel;

    class LoginController;

    class MainController {
    public:
        MainController();

        MainController(MainView *window, MainModel *model);

        ~MainController();

        void setWindow(MainView *window);

        void setModel(MainModel *model);

        void login(std::string name, std::string password);

        void login(int id);

        LoginController *get_view_controller();

    private:
        MainView *view;
        MainModel *model;

        // controllers
        LoginController *login_controller;
        std::mutex login_mutex;
    };
}

#endif //ELABORATO_ING_SW_MAINCONTROLLER_HPP
