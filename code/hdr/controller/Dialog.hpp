//
// Created by Mirko Morati on 14/09/17.
//

#ifndef ELABORATO_ING_SW_DIALOG_HPP
#define ELABORATO_ING_SW_DIALOG_HPP

#include "../view/Dialog.hpp"

namespace mm {
    namespace view {
        class Dialog;
    }

    namespace controller {
        class Dialog {
        public:
            virtual ~Dialog();

            virtual void ok_handler() = 0;

            virtual void cancel_handler() = 0;

            virtual void set_view() = 0;

            void show_dialog();

        protected:
            view::Dialog *view;
        };
    }
}


#endif //ELABORATO_ING_SW_DIALOG_HPP
