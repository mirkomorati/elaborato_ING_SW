//
// Created by Mirko Morati on 03/08/17.
//

#ifndef ELABORATO_ING_SW_SELECTDATEDIALOG_HPP
#define ELABORATO_ING_SW_SELECTDATEDIALOG_HPP

#include "../view/SelectDateDialog.hpp"
#include "../time_utilities/DateBy.hpp"
#include "Patient.hpp"

namespace mm {
    namespace view {
        class SelectDateDialog;
    }

    namespace controller {
        class Patient;

        class SelectDateDialog {
        public:
            virtual ~SelectDateDialog();

            void show_dialog();

            void ok_handler();

            void cancel_handler();

            void set_view();

            void set_parent(Patient *parent);

            util::DateBy get_date();

        private:
            controller::Patient *parent;
            view::SelectDateDialog *view;
            util::DateBy date_by;
        };
    }
}

#endif //ELABORATO_ING_SW_SELECTDATEDIALOG_HPP
