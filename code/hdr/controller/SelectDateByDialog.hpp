//
// Created by Mirko Morati on 03/08/17.
//

#ifndef ELABORATO_ING_SW_SELECTDATEBYDIALOG_HPP
#define ELABORATO_ING_SW_SELECTDATEBYDIALOG_HPP

#include "../view/SelectDateByDialog.hpp"
#include "../time_utilities/DateBy.hpp"
#include "Patient.hpp"

namespace mm {
    namespace view {
        class SelectDateByDialog;
    }

    namespace controller {
        class Patient;

        class SelectDateByDialog {
        public:
            virtual ~SelectDateByDialog();

            void show_dialog();

            void ok_handler();

            void cancel_handler();

            void set_view();

            void set_parent(Patient *parent);

            util::DateBy get_date();

        private:
            controller::Patient *parent;
            view::SelectDateByDialog *view;
            util::DateBy date_by;
        };
    }
}

#endif //ELABORATO_ING_SW_SELECTDATEDIALOG_HPP
