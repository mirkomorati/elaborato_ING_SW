//
// Created by Mirko Morati on 14/09/17.
//

#ifndef ELABORATO_ING_SW_SELECTDATEDIALOGVIEW_HPP
#define ELABORATO_ING_SW_SELECTDATEDIALOGVIEW_HPP

#include "../controller/SelectDateDialog.hpp"
#include "Dialog.hpp"

namespace mm {
    namespace controller {
        class SelectDateDialog;
    }

    namespace view {
        class SelectDateDialog : public view::Dialog {
        public:
            SelectDateDialog();

            void
            set_ok_handler(mm::controller::Dialog *controller, void (mm::controller::Dialog::*handler)(void)) override;

            void set_cancel_handler(mm::controller::Dialog *controller,
                                    void (mm::controller::Dialog::*handler)(void)) override;
        };
    }
}


#endif //ELABORATO_ING_SW_SELECTDATEDIALOG_HPP
