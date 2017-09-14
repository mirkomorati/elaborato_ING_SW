//
// Created by Mirko Morati on 03/08/17.
//

#ifndef ELABORATO_ING_SW_SELECTDATEBYDIALOGVIEW_HPP
#define ELABORATO_ING_SW_SELECTDATEBYDIALOGVIEW_HPP

#include "../controller/SelectDateByDialog.hpp"

namespace mm {
    namespace controller {
        class SelectDateByDialog;
    }

    namespace view {
        class SelectDateByDialog {
        public:
            void set_controller(controller::SelectDateByDialog *controller);

            void show_dialog();

            void dispose_dialog();
        };
    }
}


#endif //ELABORATO_ING_SW_SELECTDATEDIALOGVIEW_HPP
