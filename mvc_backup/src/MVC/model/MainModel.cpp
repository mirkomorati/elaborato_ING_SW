//
// Created by Mirko Morati on 30/06/17.
//

#include "../../../../code/hdr/MVC/model/MainModel.hpp"
#include "../../../../code/hdr/DBMaster.hpp"



std::vector<std::tuple<std::string, std::string, int>>
mm::MainModel::get_login_data() {
    return LoginModel().get_login_data();
}

mm::MainModel::MainModel(mm::MainController *controller) :
        controller(controller) {
}

mm::MainModel::~MainModel() {
}
