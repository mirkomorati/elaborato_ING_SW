//
// Created by Mirko Morati on 03/08/17.
//

#ifndef ELABORATO_ING_SW_SELECTDATEBYDIALOGVIEW_HPP
#define ELABORATO_ING_SW_SELECTDATEBYDIALOGVIEW_HPP

#include "Dialog.hpp"

namespace mm {
    namespace view {
        class SelectDateByDialog : public Dialog {
        public:
            SelectDateByDialog();

            void
            set_ok_handler(mm::controller::Dialog *controller, void (mm::controller::Dialog::*handler)(void)) override;

            void set_cancel_handler(mm::controller::Dialog *controller,
                                    void (mm::controller::Dialog::*handler)(void)) override;
        };
    }
}


#endif //ELABORATO_ING_SW_SELECTDATEDIALOGVIEW_HPP
