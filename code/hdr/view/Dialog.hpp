//
// Created by Mirko Morati on 14/09/17.
//

#ifndef ELABORATO_ING_SW_DIALOGVIEW_HPP
#define ELABORATO_ING_SW_DIALOGVIEW_HPP

#include <string>
#include <gtkmm/button.h>
#include "../controller/Dialog.hpp"
#include "../RefBuilder.hpp"

namespace mm {
    namespace view {
        class Dialog {
        public:
            Dialog(std::string name);

            void show_dialog();

            void dispose_dialog();

            virtual void
            set_ok_handler(mm::controller::Dialog *controller, void (mm::controller::Dialog::*handler)(void)) = 0;

            virtual void
            set_cancel_handler(mm::controller::Dialog *controller, void (mm::controller::Dialog::*handler)(void)) = 0;

        protected:
            const std::string name;
            sigc::connection c_ok, c_cancel;
        };
    }
}


#endif //ELABORATO_ING_SW_DIALOGVIEW_HPP
