//
// Created by Mirko Morati on 03/08/17.
//

#ifndef ELABORATO_ING_SW_SELECTDATEDIALOGVIEW_HPP
#define ELABORATO_ING_SW_SELECTDATEDIALOGVIEW_HPP

#include "../controller/SelectDateDialogController.hpp"

namespace mm {
    class SelectDateDialogController;

    class SelectDateDialogView {
    public:
        void set_controller(SelectDateDialogController *controller);

        void show_dialog();

        void dispose_dialog();

    private:
    };
}


#endif //ELABORATO_ING_SW_SELECTDATEDIALOGVIEW_HPP
