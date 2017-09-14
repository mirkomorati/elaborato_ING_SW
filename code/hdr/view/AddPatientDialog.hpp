//
// Created by Mirko Morati on 14/09/17.
//

#ifndef ELABORATO_ING_SW_ADDPATIENTDIALOGVIEW_HPP
#define ELABORATO_ING_SW_ADDPATIENTDIALOGVIEW_HPP

#include "../controller/SelectDateDialog.hpp"

namespace mm {
    namespace controller {
        class AddPatientDialog;
    }

    namespace view {
        class AddPatientDialog {
        public:
            void set_controller(controller::AddPatientDialog *controller);

            void show_dialog();

            void dispose_dialog();
        };
    }
}


#endif //ELABORATO_ING_SW_ADDPATIENTDIALOGVIEW_HPP
