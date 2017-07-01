//
// Created by Mirko Morati on 30/06/17.
//

#include "../../../hdr/MVC/model/MainModel.hpp"
#include "../../../hdr/DBMaster.hpp"

mm::MainModel::MainModel(mm::MainController *controller) : controller(controller) {

}

std::vector<std::pair<std::string, std::string>> mm::MainModel::getLoginData() {
    std::pair<std::string, std::string> login_data;
    std::vector<std::pair<std::string, std::string>> to_ret;
    auto &db = DBMaster::get_instance();
    auto table = db.get_table("login", 2, 0);
    for (auto row : table) {
        login_data.first = row[0].get_str();
        login_data.second = row[1].get_str();
        to_ret.push_back(login_data);
    }
    return to_ret;
}
