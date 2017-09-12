//
// Created by Mirko Morati on 04/07/17.
//

#ifndef ELABORATO_ING_SW_LOGIN_HPP
#define ELABORATO_ING_SW_LOGIN_HPP

#include "../DBMaster.hpp"
#include <vector>
#include <tuple>

namespace mm {
    namespace model {
        namespace authentication {

            struct Login : ISerializable {
                std::string user_name;
                std::string password;
                int regional_id;

                map<string, Serialized> serialize() const override;

                void unserialize(map<string, Serialized> map) override;

                string get_table_name() const override;

                vector<string> get_primary_key() const override;
            };

            bool check_login(std::string usr, std::string psw, authentication::Login &account);
        }
    }
}


#endif //ELABORATO_ING_SW_LOGINMODEL_HPP
