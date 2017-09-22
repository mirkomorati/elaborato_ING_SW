//
// Created by Mirko Morati on 04/07/17.
//

#ifndef ELABORATO_ING_SW_LOGIN_HPP
#define ELABORATO_ING_SW_LOGIN_HPP

#include "../DBMaster.hpp"
#include "../interfaces/ISubject.hpp"
#include <vector>
#include <tuple>

namespace mm {
    namespace model {
        namespace authentication {

            struct Login : public ISerializable, public ISubject {
                friend bool check_login(std::string usr, std::string psw);

                bool is_changed;
                std::string user_name;
                std::string password;
                int regional_id;

                map<string, Serialized> serialize() const override;

                void unserialize(map<string, Serialized> map) override;

                string get_table_name() const override;

                vector<string> get_primary_key() const override;

                static Login &get_instance();

            private:
                explicit Login();

                Login(const Login &other) = default;

                Login &operator=(const Login &other);
            };

            bool check_login(std::string usr, std::string psw);
        }
    }
}


#endif //ELABORATO_ING_SW_LOGINMODEL_HPP
