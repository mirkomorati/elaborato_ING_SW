//
// Created by Noè Murr on 02/07/2017.
//

#include "../../../../code/hdr/MVC/model/LoginModel.hpp"
#include "../../../../code/hdr/DBMaster.hpp"

std::vector<std::tuple<std::string, std::string, int>>
mm::LoginModel::get_login_data() {
    auto &db = DBMaster::get_instance();
    std::tuple<std::string, std::string, int> data;
    std::vector<decltype(data)> to_return;

    auto table = db.get_table("login");

    for (auto row : table) {
        data = std::make_tuple(row[0].get_str(), row[1].get_str(), row[2].get_int());
        to_return.push_back(data);
    }

    return to_return;
}
