//
// Created by Mirko Morati on 03/08/17.
//

#ifndef ELABORATO_ING_SW_SELECTDATEDIALOGCONTROLLER_HPP
#define ELABORATO_ING_SW_SELECTDATEDIALOGCONTROLLER_HPP

#include "../view/SelectDateDialogView.hpp"

namespace mm {
    class SelectDateDialogView;

    class SelectDateDialogController {
    public:
        virtual ~SelectDateDialogController();

        void show_dialog();

        void ok_handler();

        void cancel_handler();

        void set_view();

    private:
        SelectDateDialogView *view;
    };
}

#endif //ELABORATO_ING_SW_SELECTDATEDIALOGCONTROLLER_HPP
