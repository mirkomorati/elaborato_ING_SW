//
// Created by Mirko Morati on 04/07/17.
//

#include <iostream>
#include "../hdr/LoginModel.hpp"

std::vector<std::tuple<std::string, std::string, int>>
mm::LoginModel::get_login_data() {
    auto &db = DBMaster::get_instance();

    std::tuple<std::string, std::string, int> data;
    std::vector<decltype(data)> to_return;

    auto table = db.get_table("login");

    std::cout << "Data: " << std::endl;
    for (auto row : table) {
        data = std::make_tuple(row[0].get_str(), row[1].get_str(),
                               row[2].get_int());
        std::cout << get<0>(data) << " "
                  << get<1>(data) << " "
                  << get<2>(data) << std::endl;
        to_return.push_back(data);
    }

    return to_return;

};