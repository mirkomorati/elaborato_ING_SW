//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_LOGINVIEW_HPP
#define ELABORATO_ING_SW_LOGINVIEW_HPP

#include "../controller/Main.hpp"
#include "../model/Main.hpp"
#include <gtkmm-3.0/gtkmm.h>

namespace mm {

    namespace view {
        class Login : public IObserver {
        public:
            Login(controller::Main &c);

            void update() override;

        private:
            std::shared_ptr<model::Main> model;

            void login_failed();

        };
    }
}


#endif //ELABORATO_ING_SW_LOGINVIEW_HPP
