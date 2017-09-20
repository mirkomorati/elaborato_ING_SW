//
// Created by Mirko Morati on 14/09/17.
//

#ifndef ELABORATO_ING_SW_ADDPATIENTDIALOG_HPP
#define ELABORATO_ING_SW_ADDPATIENTDIALOG_HPP

#include "../view/AddPatientDialog.hpp"
#include "SelectDateDialog.hpp"
#include "Application.hpp"

namespace mm {
    namespace view {
        class AddPatientDialog;
    }
    namespace controller {
        class AddPatientDialog : public controller::Dialog {
        public:
            AddPatientDialog();

            ~AddPatientDialog();

            void ok_handler() override;

            void cancel_handler() override;

            void set_view() override;

            void show_dialog() override;

            void select_birth_date_handler();

            void select_birth_date_get_date(util::Date date);

            void free();

            static Dialog *create();

        private:
            view::AddPatientDialog *view;
        };
    }
}


#endif //ELABORATO_ING_SW_ADDPATIENTDIALOG_HPP
