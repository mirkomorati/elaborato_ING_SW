//
// Created by Mirko Morati on 30/06/17.
//

#ifndef ELABORATO_ING_SW_MAINMODEL_HPP
#define ELABORATO_ING_SW_MAINMODEL_HPP

#include "../controller/MainController.hpp"
#include <vector>
#include <tuple>

namespace mm {
    class MainController;

    class MainModel {
    public:
        MainModel(MainController *controller);

        std::vector<std::tuple<std::string, std::string, int>> getLoginData();

    private:
        MainController *controller;

    };
}

#endif //ELABORATO_ING_SW_MAINMODEL_HPP
