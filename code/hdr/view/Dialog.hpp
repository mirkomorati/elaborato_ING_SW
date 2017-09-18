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
    namespace controller {
        class Dialog;
    }
    namespace view {
        class Dialog {
        public:
            Dialog(std::string name);

            template<class T>
            void set_button_handler(T *controller, std::string button_name, void (T::*handler)(void)) {
                Gtk::Button *button;
                RefBuilder::get_instance().get_widget(button_name, button);

                button->signal_clicked().connect(sigc::mem_fun(controller, handler));
            }

            void show_dialog();

            void dispose_dialog();

            virtual void set_combo_box(std::vector<std::string> combo_text);

        private:
            const std::string name;
        };
    }
}


#endif //ELABORATO_ING_SW_DIALOGVIEW_HPP
