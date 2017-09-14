//
// Created by Mirko Morati on 14/09/17.
//

#ifndef ELABORATO_ING_SW_ADDPATIENTDIALOG_HPP
#define ELABORATO_ING_SW_ADDPATIENTDIALOG_HPP

#include "../view/AddPatientDialog.hpp"
#include "SelectDateDialog.hpp"
#include "Patient.hpp"

namespace mm {
    namespace view {
        class AddPatientDialog;
    }

    namespace controller {
        class Patient;

        class AddPatientDialog {
        public:
            virtual ~AddPatientDialog();

            void show_dialog();

            void ok_handler();

            void cancel_handler();

            void select_birth_date_handler();

            void select_birth_date_get_date(util::Date date);

            void set_view();

            void set_parent(Patient *parent);

        private:
            controller::Patient *parent;
            view::AddPatientDialog *view;
        };
    }
}


#endif //ELABORATO_ING_SW_ADDPATIENTDIALOG_HPP
