//
// Created by Mirko Morati on 14/09/17.
//

#ifndef ELABORATO_ING_SW_SELECTDATEDIALOG_HPP
#define ELABORATO_ING_SW_SELECTDATEDIALOG_HPP

#include "../view/SelectDateDialog.hpp"
#include "../time_utilities/Date.hpp"
#include "AddPatientDialog.hpp"

namespace mm {
    namespace view {
        class SelectDateDialog;
    }

    namespace controller {
        class AddPatientDialog;

        class SelectDateDialog : public controller::Dialog {
        public:
            SelectDateDialog();

            ~SelectDateDialog();

            void ok_handler() override;

            void cancel_handler() override;

            void set_view() override;

            void show_dialog() override;

            void set_parent(AddPatientDialog *parent);

            util::Date get_date();

            void free();

            static Dialog *create();

        private:
            controller::AddPatientDialog *parent;
            view::SelectDateDialog *view;
            util::Date date;
        };
    }
}

#endif //ELABORATO_ING_SW_SELECTDATEDIALOG_HPP
