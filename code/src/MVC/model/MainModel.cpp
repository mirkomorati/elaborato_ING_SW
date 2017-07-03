//
// Created by Mirko Morati on 30/06/17.
//

#include "../../../hdr/MVC/model/MainModel.hpp"
#include "../../../hdr/DBMaster.hpp"



std::vector<std::tuple<std::string, std::string, int>>
mm::MainModel::getLoginData() {
    return login_model->getLoginData();
}

mm::MainModel::MainModel(mm::MainController *controller) :
        controller(controller) {
    login_model = new LoginModel();
}

mm::MainModel::~MainModel() {
    if (login_model) delete login_model;
}
