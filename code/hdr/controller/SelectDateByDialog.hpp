//
// Created by Mirko Morati on 03/08/17.
//

#ifndef ELABORATO_ING_SW_SELECTDATEBYDIALOG_HPP
#define ELABORATO_ING_SW_SELECTDATEBYDIALOG_HPP

#include "../view/SelectDateByDialog.hpp"
#include "../time_utilities/DateBy.hpp"
#include "Patient.hpp"

namespace mm {
    namespace controller {
        class Patient;

        class SelectDateByDialog : public controller::Dialog {
        public:
            ~SelectDateByDialog();

            void ok_handler();

            void cancel_handler();

            void set_view();

            void set_parent(Patient *parent);

            util::DateBy get_date();

        private:
            controller::Patient *parent;
            util::DateBy date_by;
        };
    }
}

#endif //ELABORATO_ING_SW_SELECTDATEDIALOG_HPP
