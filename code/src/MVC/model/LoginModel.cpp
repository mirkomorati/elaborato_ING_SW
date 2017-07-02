//
// Created by Noè Murr on 02/07/2017.
//

#include "../../../hdr/MVC/model/LoginModel.hpp"
#include "../../../hdr/DBMaster.hpp"

std::vector<std::tuple<std::string, std::string, int>>
mm::LoginModel::getLoginData() {
    auto &db = DBMaster::get_instance();
    std::tuple<std::string, std::string, int> data;
    std::vector<decltype(data)> to_return;

    auto table = db.get_table("login");

    for (auto row : table) {
        data = std::make_tuple(row[0], row[1], row[2]);
        to_return.push_back(data);
    }
}
