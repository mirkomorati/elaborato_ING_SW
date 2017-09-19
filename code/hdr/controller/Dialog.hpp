//
// Created by Mirko Morati on 14/09/17.
//

#ifndef ELABORATO_ING_SW_DIALOG_HPP
#define ELABORATO_ING_SW_DIALOG_HPP

namespace mm {
    namespace controller {
        class Dialog {
        public:
            virtual void ok_handler() = 0;

            virtual void cancel_handler() = 0;

            virtual void set_view() = 0;

            virtual void show_dialog() = 0;
        };
    }
}


#endif //ELABORATO_ING_SW_DIALOG_HPP
