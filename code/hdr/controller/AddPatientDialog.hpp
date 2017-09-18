//
// Created by Mirko Morati on 14/09/17.
//

#ifndef ELABORATO_ING_SW_ADDPATIENTDIALOG_HPP
#define ELABORATO_ING_SW_ADDPATIENTDIALOG_HPP

#include "../view/AddPatientDialog.hpp"
#include "SelectDateDialog.hpp"
#include "Patient.hpp"

namespace mm {
    namespace controller {
        class AddPatientDialog : public controller::Dialog {
        public:
            AddPatientDialog();

            ~AddPatientDialog();

            void ok_handler();

            void cancel_handler();

            void set_view();

            void select_birth_date_handler();

            void select_birth_date_get_date(util::Date date);
        };
    }
}


#endif //ELABORATO_ING_SW_ADDPATIENTDIALOG_HPP
