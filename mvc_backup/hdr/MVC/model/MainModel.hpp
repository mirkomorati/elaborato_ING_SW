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
        MainModel(MainController *controller);

        virtual ~MainModel();

        std::vector<std::tuple<std::string, std::string, int>> get_login_data();

    private:
        MainController *controller;

    };
}

#endif //ELABORATO_ING_SW_MAINMODEL_HPP
