//
// Created by Mirko Morati on 04/07/17.
//

#include "../../hdr/model/Authentication.hpp"

bool mm::model::authentication::check_login(std::string usr, std::string psw, authentication::Login &account) {
    Login login;
    try {
        DBMaster::get_instance().extract_from_db(login, std::move(usr));
    } catch (record_not_found_error &e) { // wrong username
        return false;
    }

    if (login.password != psw) return false; // wrong password

    // login successful
    account = std::move(login);
    return true;
};

map<string, mm::Serialized> mm::model::authentication::Login::serialize() const {
    std::map<std::string, mm::Serialized> serialized;
    serialized["name"] = user_name;
    serialized["password"] = password;
    serialized["regional_id"] = regional_id;
    return serialized;
}

void mm::model::authentication::Login::unserialize(map<string, mm::Serialized> map) {
    user_name = map["name"].get_str();
    password = map["password"].get_str();
    regional_id = map["regional_id"].get_int();
}

string mm::model::authentication::Login::get_table_name() const {
    return "login";
}

vector<string> mm::model::authentication::Login::get_primary_key() const {
    return {"name"};
}
