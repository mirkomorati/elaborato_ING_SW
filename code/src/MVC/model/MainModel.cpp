//
// Created by Mirko Morati on 30/06/17.
//

#include "../../../hdr/MVC/model/MainModel.hpp"
#include "../../../hdr/DBMaster.hpp"

mm::MainModel::MainModel(mm::MainController *controller) : controller(
    controller) {

}

std::vector<std::tuple<std::string, std::string, int>>
mm::MainModel::getLoginData() {
    std::tuple<std::string, std::string, int> login_data;
    std::vector<std::tuple<std::string, std::string, int>> to_ret;
    auto &db = DBMaster::get_instance();
    auto table = db.get_table("login");
    for (auto row : table) {
        login_data = std::make_tuple(row[0].get_str(), row[1].get_str(),
                                     row[2].get_int());
        to_ret.push_back(login_data);
    }
    return to_ret;
}
