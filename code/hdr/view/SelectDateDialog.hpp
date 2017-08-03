//
// Created by Mirko Morati on 03/08/17.
//

#ifndef ELABORATO_ING_SW_SELECTDATEDIALOGVIEW_HPP
#define ELABORATO_ING_SW_SELECTDATEDIALOGVIEW_HPP

#include "../controller/SelectDateDialog.hpp"

namespace mm {
    namespace controller {
        class SelectDateDialog;
    }

    namespace view {
        class SelectDateDialog {
        public:
            void set_controller(controller::SelectDateDialog *controller);

            void show_dialog();

            void dispose_dialog();

        private:
        };
    }
}


#endif //ELABORATO_ING_SW_SELECTDATEDIALOGVIEW_HPP
