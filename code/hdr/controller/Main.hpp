//
// Created by Noè Murr on 03/07/2017.
//

#ifndef ELABORATO_ING_SW_MAINCONTROLLER_HPP
#define ELABORATO_ING_SW_MAINCONTROLLER_HPP


#include "Application.hpp"
#include "../model/Main.hpp"
#include "../interfaces/ISubject.hpp"
#include <gdk/gdk.h>

namespace mm {
    namespace controller {

        class Main : public ISubject {
        public:
            Main();

            void about_dialog_response(int response_id);

            void about_dialog_handler();

            bool about_dialog_link(const Glib::ustring &uri);

            bool key_pressed_handler(GdkEventKey *event);

            const std::shared_ptr<model::Main> &get_model() const;

            void login_button_handler();

        private:
            std::shared_ptr<model::Main> model;
        };
    }
}


#endif //ELABORATO_ING_SW_MAINCONTROLLER_HPP
