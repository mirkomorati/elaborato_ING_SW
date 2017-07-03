//
// Created by Mirko Morati on 30/06/17.
//

#ifndef ELABORATO_ING_SW_MAINMODEL_HPP
#define ELABORATO_ING_SW_MAINMODEL_HPP

#include "../controller/MainController.hpp"
#include "../view/MainView.hpp"
#include "LoginModel.hpp"
#include <vector>
#include <tuple>

namespace mm {
    class MainController;

    class LoginModel;

    class MainView;

    class MainModel {
    public:
        MainModel(MainController *controller, MainView *view);

        virtual ~MainModel();

        std::vector<std::tuple<std::string, std::string, int>> getLoginData();

        LoginModel *get_login_model();

    private:
        MainController *controller;
        MainView *view;
        LoginModel *login_model;

    };
}

#endif //ELABORATO_ING_SW_MAINMODEL_HPP
