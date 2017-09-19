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
            SelectDateByDialog();

            ~SelectDateByDialog();

            void ok_handler() override;

            void cancel_handler() override;

            void set_view() override;

            void set_parent(Patient *parent);

            util::DateBy get_date();

            void free();

            static Dialog *create();

        private:
            controller::Patient *parent;
            view::SelectDateByDialog *view;
            util::DateBy date_by;
        };
    }
}

#endif //ELABORATO_ING_SW_SELECTDATEDIALOG_HPP
