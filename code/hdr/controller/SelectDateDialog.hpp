//
// Created by Mirko Morati on 03/08/17.
//

#ifndef ELABORATO_ING_SW_SELECTDATEDIALOG_HPP
#define ELABORATO_ING_SW_SELECTDATEDIALOG_HPP

#include "../view/SelectDateDialog.hpp"

namespace mm {
    namespace view {
        class SelectDateDialog;
    }

    namespace controller {
        class SelectDateDialog {
        public:
            virtual ~SelectDateDialog();

            void show_dialog();

            void ok_handler();

            void cancel_handler();

            void set_view();

        private:
            view::SelectDateDialog *view;
        };
    }
}

#endif //ELABORATO_ING_SW_SELECTDATEDIALOG_HPP
